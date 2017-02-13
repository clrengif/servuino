#ifndef MOUSE_H_ 
#define MOUSE_H_ 

#define MOUSE_LEFT    1
#define MOUSE_RIGHT   2
#define MOUSE_MIDDLE  4
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE)


class mouse {

public:
  void begin();
  void click(uint_8t b = MOUSE_LEFT);
  void end();
  void move(int x, int y, int wheel = 0);
  void press(uint_8t b = MOUSE_LEFT);
  void release(uint_8t b = MOUSE_LEFT);
  bool isPressed(uint_8t b = MOUSE_LEFT);
};
mouse Mouse;

#endif