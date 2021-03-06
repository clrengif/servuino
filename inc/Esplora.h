#ifndef ESPLORA_H_ 
#define ESPLORA_H_ 

#include "esplora_pins.h"
const byte JOYSTICK_BASE  = 16; // it's a "virtual" channel: its ID won't conflict with real ones

const byte MAX_CHANNELS   = 13;

const byte CH_SWITCH_1    = 0;
const byte CH_SWITCH_2    = 1;
const byte CH_SWITCH_3    = 2;
const byte CH_SWITCH_4    = 3;
const byte CH_SLIDER      = 4;
const byte CH_LIGHT       = 5;
const byte CH_TEMPERATURE = 6;
const byte CH_MIC         = 7;
const byte CH_TINKERKIT_A = 8;
const byte CH_TINKERKIT_B = 9;
const byte CH_JOYSTICK_SW = 10;
const byte CH_JOYSTICK_X  = 11;
const byte CH_JOYSTICK_Y  = 12;

const byte SIM_SWITCH_1    = 1;
const byte SIM_SWITCH_2    = 2;
const byte SIM_SWITCH_3    = 3;
const byte SIM_SWITCH_4    = 4;
const byte SIM_SLIDER      = 7;
const byte SIM_LIGHT       = 8;
const byte SIM_TEMPERATURE = 11;
const byte SIM_MIC         = 12;
const byte SIM_TINKERKIT_A = 13;
const byte SIM_TINKERKIT_B = 14;
const byte SIM_JOYSTICK_SW = 15;
const byte SIM_JOYSTICK_X  = 16;
const byte SIM_JOYSTICK_Y  = 17;
const byte SIM_RED         = 5;
const byte SIM_GREEN       = 9;
const byte SIM_BLUE        = 10;
const byte SIM_ACCEL_X     = 23;
const byte SIM_ACCEL_Y     = 29;
const byte SIM_ACCEL_Z     = 24;
const byte SIM_BUZZER      = 6;


/*
 * The following constants can be used with the readButton()
 * method.
 */

const byte SWITCH_1       = 1;
const byte SWITCH_2       = 2;
const byte SWITCH_3       = 3;
const byte SWITCH_4       = 4;

const byte SWITCH_DOWN  = SWITCH_1;
const byte SWITCH_LEFT  = SWITCH_2;
const byte SWITCH_UP    = SWITCH_3;
const byte SWITCH_RIGHT = SWITCH_4;

const byte JOYSTICK_DOWN  = JOYSTICK_BASE;
const byte JOYSTICK_LEFT  = JOYSTICK_BASE+1;
const byte JOYSTICK_UP    = JOYSTICK_BASE+2;
const byte JOYSTICK_RIGHT = JOYSTICK_BASE+3;

const boolean PRESSED   = LOW;
const boolean RELEASED  = HIGH;

/*
 * The following constants can be used with the readTemperature()
 * method to specify the desired scale.
 */
const byte DEGREES_C = 0;
const byte DEGREES_F = 1;

/*
 * The following constants can be used with the readAccelerometer()
 * method to specify the desired axis to return.
 */
const byte X_AXIS = 0;
const byte Y_AXIS = 1;
const byte Z_AXIS = 2;


class esplora {
private:
  byte lastRed;
  byte lastGreen;
  byte lastBlue;
  unsigned long duration_left;

public:
  int readSlider();
  int readLightSensor();
  int readTemperature(byte scale);
  int readMicrophone();
  int readJoystickSwitch();
  int readJoystickButton();
  int readAccelerometer(byte axis);
  int readButton(byte button);
  int readJoystickX();
  int readJoystickY();
  void writeRGB(byte red, byte green, byte blue);
  void writeRed(byte red);
  void writeGreen(byte green);
  void writeBlue(byte blue);
  byte readRed();
  byte readGreen();
  byte readBlue();
  void noTone();
  void tone(unsigned int freq);
  void tone(unsigned int freq, unsigned long duration);
};
esplora Esplora;

#endif