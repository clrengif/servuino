#ifndef ESPLORA_H_ 
#define ESPLORA_H_ 

class esplora {
private:
  byte lastRed;
  byte lastGreen;
  byte lastBlue;

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