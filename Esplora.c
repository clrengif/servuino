/*
  Esplora.cpp - Arduino simulator Esplora board library
  Written by Owen Brasier

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Esplora.h"
#include "global_variables.h"

/*
 * The following constants tell, for each accelerometer
 * axis, which values are returned when the axis measures
 * zero acceleration.
 */
const int ACCEL_ZERO_X = 320;
const int ACCEL_ZERO_Y = 330;
const int ACCEL_ZERO_Z = 310;

typedef uint8_t byte;

const byte MUX_ADDR_PINS[] = { A0, A1, A2, A3 };
const byte MUX_COM_PIN = A4;

const int JOYSTICK_DEAD_ZONE = 100;

const byte RED_PIN    = 5;
const byte BLUE_PIN   = 9;
const byte GREEN_PIN  = 10;

const byte BUZZER_PIN = 6;

// non-multiplexer Esplora pins: 
// Accelerometer: x-A5, y-A11, z-A6
// External outputs: D3, D11
// Buzzer: D6
// RGB Led: red-D5, green-D10, blue-D9
// Led 13: D13

const byte ACCEL_X_PIN = A5;
const byte ACCEL_Y_PIN = A11;
const byte ACCEL_Z_PIN = A6;

const byte LED_PIN     = 13;

//==========================================
// Esplora
//==========================================
int esplora::readSlider() {
  m_pins.lock();
  increment_counter(128); // 128.2
  int val = x_pinValue[SIM_SLIDER];
  m_pins.unlock();
  return val;
}

int esplora::readLightSensor() {
//  increment_counter(128); // 128.2
  return 0;

}

int esplora::readTemperature(byte scale) {
//  increment_counter(128); // 128.2
  return 0;

}

int esplora::readMicrophone() {
//  increment_counter(128); // 128.2 us
  return 0;

}

int esplora::readJoystickSwitch() {
//  increment_counter(30); // takes 30.2 us
  return 0;

}

int esplora::readJoystickButton() {
//  increment_counter(32); // 31.9 us
  return 0;

}

int esplora::readAccelerometer(byte axis) {
  increment_counter(112); // 112.1
  int val;
  m_pins.lock();
  switch (axis) {
    case X_AXIS: return x_pinValue[SIM_ACCEL_X];
    case Y_AXIS: return x_pinValue[SIM_ACCEL_Y]; 
    case Z_AXIS: return x_pinValue[SIM_ACCEL_Z];
    default: return 0;
  }
}

int esplora::readButton(byte button) {
  increment_counter(136); // 136.01 us
  m_pins.lock();
  int val = (x_pinValue[button] > 0) ? HIGH : LOW;
  m_pins.unlock();
  return val;

}

int esplora::readJoystickX() {
//  increment_counter(128);
  return 0;

}

int esplora::readJoystickY() {
//  increment_counter(128);
  return 0;

}

void esplora::writeRGB(byte red, byte green, byte blue) {
  writeRed(red);
  writeGreen(green);
  writeBlue(blue);
}

void esplora::writeRed(byte red) {
  increment_counter(1);
  m_pins.lock();
  x_pinValue[SIM_RED] = red;
  lastRed = red;
  m_pins.unlock();
  send_pin_update();
  int bright = map(red, 0, 255, 0, 9);
  m_leds.lock();
  x_leds[0] = bright;
  m_leds.unlock();
  send_led_update();
}

void esplora::writeGreen(byte green) {
  increment_counter(1);
  m_pins.lock();
  x_pinValue[SIM_GREEN] = green;
  lastGreen = green;
  m_pins.unlock();
  send_pin_update();
  int bright = map(green, 0, 255, 0, 9);
  m_leds.lock();
  x_leds[1] = bright;
  m_leds.unlock();
  send_led_update();
}

void esplora::writeBlue(byte blue) {
  increment_counter(1);
  m_pins.lock();
  x_pinValue[SIM_BLUE] = blue;
  lastBlue = blue;
  m_pins.unlock();
  send_pin_update();
  int bright = map(blue, 0, 255, 0, 9);
  m_leds.lock();
  x_leds[2] = bright;
  m_leds.unlock();
  send_led_update();
}

byte esplora::readRed() {
  return lastRed;
}

byte esplora::readGreen() {
  return lastGreen;
}

byte esplora::readBlue() {
  return lastBlue;
}

void esplora::noTone() {
  increment_counter(5);
  m_pins.lock();
  x_pinValue[SIM_BUZZER] = 0;
  m_pins.unlock();
  send_pin_update();
}

void esplora::tone(unsigned int freq) {
  if (freq > 0) {
    increment_counter(7);
    m_pins.lock();
    x_pinValue[SIM_BUZZER] = freq;
    m_pins.unlock();
    send_pin_update();
  }
  else {
    noTone(); 
  }
}

// TODO: implement duration timeout
void esplora::tone(unsigned int freq, unsigned long duration) {
  if (freq > 0 && duration > 0) {
    increment_counter(7);
    m_pins.lock();
    duration_left = duration;
    x_pinValue[SIM_BUZZER] = freq;
    m_pins.unlock();
  }
  else {
    noTone();
  }    
  send_pin_update();
}