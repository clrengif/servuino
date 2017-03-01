/*  Servuino is a Arduino Simulator Engine
    Copyright (C) 2012  Benny Saxen

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <fstream>
#include <math.h>
#include <sys/inotify.h>
#include "common.h"
#include <mutex>
#include "global_variables.h"

//===================================
// Simulator status
int x_pinValue[MAX_TOTAL_PINS];
int x_leds[25] = {0};
int x_pinMode[MAX_TOTAL_PINS];
int x_pinDigValue[MAX_TOTAL_PINS];
int x_pinAnaValue[MAX_TOTAL_PINS];
int x_pinRW[MAX_TOTAL_PINS];

int g_attachedPin[MAX_TOTAL_PINS];
int g_interruptType[MAX_TOTAL_PINS];

int g_curStep  =  0;
int g_curLoop  =  0;
int g_nDigPins = 14;
int g_nAnaPins =  6;
int g_nTotPins = MAX_TOTAL_PINS;

int g_doInterrupt = S_NO;
int g_serialMode = S_OFF;

char g_custText[120][120][100];


uint64_t micros_elapsed = 0;
mutex elapsed;
//===================================


int   anaPinPos[MAX_PIN_ANALOG_MEGA];
int   c_analogPin[MAX_PIN_ANALOG_MEGA];

int   digPinPos[MAX_PIN_DIGITAL_MEGA];
int   c_digitalPin[MAX_PIN_DIGITAL_MEGA];
int   digitalMode[MAX_PIN_DIGITAL_MEGA];

int   interruptMode[MAX_PIN_IR_MEGA];

int   paceMaker = 0;
int   baud = 0;
int   error = 0;
int   logging = S_NO;
int   serialSize = 1;
int   serialMode = S_OFF;
int   scenAnalog    = 0;
int   scenDigital   = 0;
int   scenInterrupt = 0;


int   confLogLev  =   0;

int g_nloop      = 0;
int g_scenSource = 0;
int g_pinType    = 0;
int g_pinNo      = 0;
int g_pinValue   = 0;
int g_pinStep    = 0;
int g_action     = 0;

int g_allowInterrupt   = S_YES;
int g_ongoingInterrupt = S_NO;
int g_interpolation    = S_NO;

int g_row_setup = 0;
int g_row_loop = 0;



#include "arduino.h"
#include "code.h"
#include "common_lib.c"
#include "servuino.h"
#include "servuino_lib.c"
#include "arduino_lib.c"
#include "Esplora.c"

#include "sketch/sketch.ino"

atomic<bool> running(true);


void
check_suspend() {
  unique_lock<mutex> lk(m_suspend);
  cv_suspend.wait(lk, []{return suspend == false;});
}

// Shutdown if we receive a shutdown signal
void
check_shutdown() {
  bool stop = false;
  if (shutdown)
    stop = true;
  if (stop) {
    send_pin_update();
    send_led_update();
    //terminate();
  }
}

void
increment_counter(int us)
{
  elapsed.lock();
  micros_elapsed += us;
  elapsed.unlock();
  check_suspend();
  check_shutdown();
}

void run_code()
{
  setup();
  increment_counter(1032);
  while (running) {
    g_curLoop++;
    loop();
  }
}


int run_servuino()
{
  int x, i;

  if (g_boardType == UNO)g_nDigPins = MAX_PIN_DIGITAL_UNO;
  if (g_boardType == MEGA)g_nDigPins = MAX_PIN_DIGITAL_MEGA;

  //boardInit();
  //readCustom(); // Get customized log text from sketch
  g_scenSource = 0;
  run_code();
  return EXIT_SUCCESS;
}

