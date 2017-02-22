#include "Esplora.h"

//==========================================
// Esplora
//==========================================
int esplora::readSlider() {
  cout << "called Esplora.readSlider()" << endl;
  return 0;
}

int esplora::readLightSensor() {
  cout << "called Esplora.readLightSensor()" << endl;
  return 0;

}

int esplora::readTemperature(byte scale) {
  cout << "called Esplora.readTemperature()" << endl;
  return 0;

}

int esplora::readMicrophone() {
  cout << "called Esplora.readMicrophone()" << endl;
  return 0;

}

int esplora::readJoystickSwitch() {
  cout << "called Esplora.readJoystickSwitch()" << endl;
  return 0;

}

int esplora::readJoystickButton() {
  cout << "called Esplora.readJoystickButton()" << endl;
  return 0;

}

int esplora::readAccelerometer(byte axis) {
  cout << "called Esplora.readAccelerometer()" << endl;
  return 0;

}

int esplora::readButton(byte button) {
  cout << "called Esplora.readButton()" << endl;
  return 0;

}

int esplora::readJoystickX() {
  cout << "called Esplora.readJoystickX()" << endl;
  return 0;

}

int esplora::readJoystickY() {
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
  cout << "called Esplora.writeRed()" << endl;
  lastRed = red;

}

void esplora::writeGreen(byte green) {
  cout << "called Esplora.writeGreen()" << endl;
  lastGreen = green;

}

void esplora::writeBlue(byte blue) {
  cout << "called Esplora.writeBlue()" << endl;
  lastBlue = blue;
}

byte esplora::readRed() {
  cout << "called Esplora.readRed()" << endl;
  return lastRed;

}

byte esplora::readGreen() {
  cout << "called Esplora.readGreen()" << endl;
  return lastGreen;

}

byte esplora::readBlue() {
  cout << "called Esplora.readBlue()" << endl;
  return lastBlue;

}

void esplora::noTone() {
  cout << "called Esplora.noTone()" << endl;

}

void esplora::tone(unsigned int freq) {
  cout << "called Esplora.tone()" << endl;

}

void esplora::tone(unsigned int freq, unsigned long duration) {
  cout << "called Esplora.tone(freq, dur)" << endl;

}