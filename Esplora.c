#include "Esplora.h"

//==========================================
// Esplora
//==========================================
int esplora::readSlider() {
  cout << "called Esplora.readSlider()" << endl;
  increment_counter(50);
  return 0;
}

int esplora::readLightSensor() {
  increment_counter(50);
  cout << "called Esplora.readLightSensor()" << endl;
  return 0;

}

int esplora::readTemperature(byte scale) {
  increment_counter(50);
  cout << "called Esplora.readTemperature()" << endl;
  return 0;

}

int esplora::readMicrophone() {
  increment_counter(50);
  cout << "called Esplora.readMicrophone()" << endl;
  return 0;

}

int esplora::readJoystickSwitch() {
  increment_counter(50);
  cout << "called Esplora.readJoystickSwitch()" << endl;
  return 0;

}

int esplora::readJoystickButton() {
  increment_counter(50);
  cout << "called Esplora.readJoystickButton()" << endl;
  return 0;

}

int esplora::readAccelerometer(byte axis) {
  increment_counter(115);
  cout << "called Esplora.readAccelerometer()" << endl;
  return 0;

}

int esplora::readButton(byte button) {
  increment_counter(50);
  cout << "called Esplora.readButton()" << endl;
  return 0;

}

int esplora::readJoystickX() {
  increment_counter(50);
  cout << "called Esplora.readJoystickX()" << endl;
  return 0;

}

int esplora::readJoystickY() {
  increment_counter(50);
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
  increment_counter(50);
  cout << "called Esplora.writeRed()" << endl;
  lastRed = red;

}

void esplora::writeGreen(byte green) {
  increment_counter(50);
  cout << "called Esplora.writeGreen()" << endl;
  lastGreen = green;

}

void esplora::writeBlue(byte blue) {
  increment_counter(50);
  cout << "called Esplora.writeBlue()" << endl;
  lastBlue = blue;
}

byte esplora::readRed() {
  increment_counter(50);
  cout << "called Esplora.readRed()" << endl;
  return lastRed;

}

byte esplora::readGreen() {
  increment_counter(50);
  cout << "called Esplora.readGreen()" << endl;
  return lastGreen;

}

byte esplora::readBlue() {
  increment_counter(50);
  cout << "called Esplora.readBlue()" << endl;
  return lastBlue;

}

void esplora::noTone() {
  increment_counter(50);
  cout << "called Esplora.noTone()" << endl;

}

void esplora::tone(unsigned int freq) {
  increment_counter(50);
  cout << "called Esplora.tone()" << endl;

}

void esplora::tone(unsigned int freq, unsigned long duration) {
  increment_counter(50);
  cout << "called Esplora.tone(freq, dur)" << endl;

}