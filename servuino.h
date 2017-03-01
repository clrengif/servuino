#ifndef SERVUINO_H_
#define SERVUINO_H_
void interruptNow();
void writeStatus();
void updateFromRegister();
void digitalWrite(int pin,int value);
int  digitalRead(int pin);

char  interruptType[50][80];
void  (*interrupt[9])();

void increment_counter(int us);


#define R_PORT 1
#define R_DDR  2
#define R_PIN  3

void  bitWrite(unsigned int *x, int n,int b);
int   bitRead(int x, int n);
int   readRegister(int reg, int port);
void  writeRegister(int digital, int reg, int port, int value);
void  registerLog();
void  setPINRegister(int step); 

#endif
