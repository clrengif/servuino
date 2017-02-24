#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/epoll.h>
#include <sys/inotify.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <chrono>
#include <cstdarg>
#include <string>
using namespace std;
using namespace literals::string_literals;
#include "servuino.cpp"


extern "C" {
#include "buffer.h"
#include "json.h"
}

mutex write_update;
mutex m_suspend;
mutex m_screen;
mutex m_code;
condition_variable suspend_cv;

// tells the code thread to shutdown, suspend or operate in fast_mode
volatile bool shutdown = false;
bool suspend = false;
bool fast_mode = false;

// File descriptor to write ___device_updates.
int updates_fd = -1;


void msg(char const * const message)
{
  m_screen.lock();
  cout << message << endl;
  m_screen.unlock();
}

// to get appendf to work
inline int
min(int a, int b)
{
  return (a < b ? a : b);
}

// timing --
// TODO: Actually handle timing.
int
get_macro_ticks() {
  return 100;
}

// Write to the output pipe
void
write_to_updates(const void* buf, size_t count, bool should_suspend = false) {
  write_update.lock();
  if (should_suspend && fast_mode) {
    m_suspend.lock();
    suspend = true;
    m_suspend.unlock();
  }
  write(updates_fd, buf, count);
  write_update.unlock();
}


void
appendf(char** str, const char* end, const char* format, ...) {
  va_list args;
  va_start(args, format);
  int n = vsnprintf(*str, end - *str, format, args);
  va_end(args);
  *str += min(end - *str, n);
}

// Write ack to say we received the data.
void
write_event_ack(const char* event_type, const char* ack_data_json) {
  char json[1024];
  char* json_ptr = json;
  char* json_end = json + sizeof(json);

  appendf(&json_ptr, json_end,
          "[{ \"type\": \"microbit_ack\", \"ticks\": %d, \"data\": { \"type\": \"%s\", \"data\": "
          "%s }}]\n",
          get_macro_ticks(), event_type, ack_data_json ? ack_data_json : "{}");

  write_to_updates(json, json_ptr - json, false);
}

// Process a button event
void
process_client_button(const json_value* data) {
  const json_value* id = json_value_get(data, "id");
  const json_value* state = json_value_get(data, "state");
  if (!id || !state || id->type != JSON_VALUE_TYPE_NUMBER ||
      state->type != JSON_VALUE_TYPE_NUMBER) {
    fprintf(stderr, "Button event missing id and/or state\n");
    return;
  }
  m_code.lock();

  m_code.unlock();
}

// Process a button event
void
process_client_temperature(const json_value* data) {
}

// Process a button event
void
process_client_accel(const json_value* data) {
}

void
process_client_magnet(const json_value* data) {

}

void
process_client_pins(const json_value* data) {

}


void
process_client_random(const json_value* data) {

}

// Handle an array of json events that we read from the pipe/file.
// All json events are at a minimum:
//   { "type": "<string>", "data": { <object> } }
void
process_client_json(const json_value* json) {
  if (json->type != JSON_VALUE_TYPE_ARRAY) {
    fprintf(stderr, "Client event JSON wasn't a list.\n");
  }
  const json_value_list* event = json->as.pairs;
  while (event) {
    if (event->value->type != JSON_VALUE_TYPE_OBJECT) {
      fprintf(stderr, "Event should be an object.\n");
      event = event->next;
      continue;
    }
    const json_value* event_type = json_value_get(event->value, "type");
    const json_value* event_data = json_value_get(event->value, "data");
    if (!event_type || !event_data || event_type->type != JSON_VALUE_TYPE_STRING ||
        event_data->type != JSON_VALUE_TYPE_OBJECT) {
      fprintf(stderr, "Event missing type and/or data.\n");
    } else {
      if (strncmp(event_type->as.string, "resume", 6) == 0) {
        m_suspend.lock();
        suspend = false;
        suspend_cv.notify_all();
        m_suspend.unlock();
      } else if (strncmp(event_type->as.string, "microbit_button", 15) == 0) {
        // Button state change.
        process_client_button(event_data);
      } else if (strncmp(event_type->as.string, "temperature", 15) == 0) {
        // Temperature change.
        process_client_temperature(event_data);
      } else if (strncmp(event_type->as.string, "accelerometer", 13) == 0) {
        // Accelerometer values change.
        process_client_accel(event_data);
      } else if (strncmp(event_type->as.string, "microbit_pin", 13) == 0) {
        // Something driving the GPIO pins.
        process_client_pins(event_data);
      } else if (strncmp(event_type->as.string, "random", 13) == 0) {
        // Injected random data (from the marker only).
        process_client_random(event_data);
      } else {
        fprintf(stderr, "Unknown event type: %s\n", event_type->as.string);
      }
      char msg_text[120];
      sprintf(msg_text, "event type: %s", event_type->as.string);
      msg(msg_text);
    }
    event = event->next;
  }
}

void
process_client_event(int fd) {
  char buf[10240];
  ssize_t len = read(fd, buf, sizeof(buf));
  if (len == sizeof(buf)) {
    fprintf(stderr, "Too much data in client event.\n");
    return;
  }
  buf[len] = 0;

  char* line_start = buf;
  while (*line_start) {
    char* line_end = strchrnul(line_start, '\n');

    json_value* json = json_parse_n(line_start, line_end - line_start);
    if (json) {
      process_client_json(json);
      json_value_destroy(json);
    } else {
      fprintf(stderr, "Invalid JSON\n");
    }

    if (!*line_end) {
      break;
    }

    line_start = line_end + 1;
  }
  cout << "processed event " << buf << endl;

  write_event_ack("arduino_event", nullptr);
}

void setup_output_pipe() {
  // Open the events pipe.
  char* updates_pipe_str = getenv("GROK_UPDATES_PIPE");
  if (updates_pipe_str != NULL) {
    updates_fd = atoi(updates_pipe_str);
  } else {
    updates_fd = open("___device_updates", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
  }

}

void code_thread_main() {
  run_servuino();

}


void
main_thread() {
  cout << "in main_thread" << endl;
  const int MAX_EVENTS = 10;
  int epoll_fd = epoll_create1(0);

  // Add non-blocking stdin to epoll set.
  struct epoll_event ev_stdin;
  fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) | O_NONBLOCK);
  ev_stdin.events = EPOLLIN;
  ev_stdin.data.fd = STDIN_FILENO;
  epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &ev_stdin);

  // Open the events pipe.
  char* client_pipe_str = getenv("GROK_CLIENT_PIPE");
  int client_fd = -1;
  int notify_fd = -1;
  int client_wd = -1;
  if (client_pipe_str != NULL) {
    cout << "found GROK_CLIENT_PIPE" << endl;
    client_fd = atoi(client_pipe_str);
    fcntl(client_fd, F_SETFL, fcntl(client_fd, F_GETFL, 0) | O_NONBLOCK);
    struct epoll_event ev_client_pipe;
    ev_client_pipe.events = EPOLLIN;
    ev_client_pipe.data.fd = client_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev_client_pipe);
  } else {
    // Create and truncate the client events file.
    client_fd = open("___client_events", O_CREAT | O_TRUNC | O_RDONLY, S_IRUSR | S_IWUSR);

    // Set up a notify for the file and add to epoll set.
    struct epoll_event ev_client;
    notify_fd = inotify_init1(0);
    client_wd = inotify_add_watch(notify_fd, "___client_events", IN_MODIFY);
    if (client_wd == -1) {
      perror("add watch");
      return;
    }
    ev_client.events = EPOLLIN;
    ev_client.data.fd = notify_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, notify_fd, &ev_client) == -1) {
      perror("epoll_ctl");
      return;
    }
  }

  int epoll_timeout = 50;
  while (!shutdown) {
    struct epoll_event events[MAX_EVENTS];
    int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, epoll_timeout);

    if (nfds == -1) {
      if (errno == EINTR) {
        // Timeout or interrupted.
        // Allow the vm branch hook to proceed.
        // Continue so that we'll catch the shutdown flag above (if it's set, otherwise continue as
        // normal).
        continue;
      }
      perror("epoll wait\n");
      exit(1);
    }

    for (int n = 0; n < nfds; ++n) {
      if (notify_fd != -1 && events[n].data.fd == notify_fd) {
        // A change occured to the ___client_events file.
        uint8_t buf[4096] __attribute__((aligned(__alignof__(inotify_event))));
        ssize_t len = read(notify_fd, buf, sizeof(buf));
        if (len == -1) {
          continue;
        }

        const struct inotify_event* event;
        for (uint8_t* p = buf; p < buf + len; p += sizeof(inotify_event) + event->len) {
          event = reinterpret_cast<inotify_event*>(p);
          if (event->wd == client_wd) {
            process_client_event(client_fd);
          }
        }
      } else if (events[n].data.fd == client_fd) {
        // A write happened to the client events pipe.
        process_client_event(client_fd);
      }
    }
  }
  if (notify_fd != -1) {
    close(notify_fd);
  }

  close(client_fd);
}

int
main(int argc, char** argv) {
  setup_output_pipe();
  thread code_thread(code_thread_main);  // run the code
  //future<void> result(async(code_thread_main));
  main_thread();                    // start reading client data
  close(updates_fd);
}