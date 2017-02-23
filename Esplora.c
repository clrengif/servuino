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
  cout << "called Esplora.readSlider()" << endl;
  increment_counter(128); // 128.2
  return 0;
}

int esplora::readLightSensor() {
  increment_counter(128); // 128.2
  cout << "called Esplora.readLightSensor()" << endl;
  return 0;

}

int esplora::readTemperature(byte scale) {
  increment_counter(128); // 128.2
  cout << "called Esplora.readTemperature()" << endl;
  return 0;

}

int esplora::readMicrophone() {
  increment_counter(128); // 128.2 us
  cout << "called Esplora.readMicrophone()" << endl;
  return 0;

}

int esplora::readJoystickSwitch() {
  increment_counter(30); // takes 30.2 us
  cout << "called Esplora.readJoystickSwitch()" << endl;
  return 0;

}

int esplora::readJoystickButton() {
  increment_counter(32); // 31.9 us
  cout << "called Esplora.readJoystickButton()" << endl;
  return 0;

}

int esplora::readAccelerometer(byte axis) {
  increment_counter(112); // 112.1
  cout << "called Esplora.readAccelerometer()" << endl;
  return 0;

}

int esplora::readButton(byte button) {
  increment_counter(136); // 136.01 us
  cout << "called Esplora.readButton()" << endl;
  return 0;

}

int esplora::readJoystickX() {
  increment_counter(128);
  cout << "called Esplora.readJoystickX()" << endl;
  return 0;

}

int esplora::readJoystickY() {
  increment_counter(128);
  cout << "called Esplora.readJoystickY()" << endl;
  return 0;

}

void esplora::writeRGB(byte red, byte green, byte blue) {
  cout << "called Esplora.writeRGB()" << endl;
  writeRed(red);
  writeGreen(green);
  writeBlue(blue);
}

void esplora::writeRed(byte red) {
  increment_counter(1);
  cout << "called Esplora.writeRed()" << endl;
  lastRed = red;

}

void esplora::writeGreen(byte green) {
  increment_counter(1);
  cout << "called Esplora.writeGreen()" << endl;
  lastGreen = green;

}

void esplora::writeBlue(byte blue) {
  increment_counter(1);
  cout << "called Esplora.writeBlue()" << endl;
  lastBlue = blue;
}

byte esplora::readRed() {
  increment_counter(0);
  cout << "called Esplora.readRed()" << endl;
  return lastRed;

}

byte esplora::readGreen() {
  increment_counter(0);
  cout << "called Esplora.readGreen()" << endl;
  return lastGreen;

}

byte esplora::readBlue() {
  increment_counter(0);
  cout << "called Esplora.readBlue()" << endl;
  return lastBlue;

}

void esplora::noTone() {
  increment_counter(5);
  cout << "called Esplora.noTone()" << endl;

}

void esplora::tone(unsigned int freq) {
  increment_counter(7);
  cout << "called Esplora.tone()" << endl;

}

void esplora::tone(unsigned int freq, unsigned long duration) {
  increment_counter(7);
  cout << "called Esplora.tone(freq, dur)" << endl;

}