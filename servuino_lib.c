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


//====================================
void clearRW()
//====================================
{
  int i;
  for (i = 0; i < g_nTotPins; i++)
  {
    x_pinRW[i] = 0;
  }
}
//====================================
void interruptPinValues()
//====================================
{
  int i;

  g_doInterrupt = S_NO;
  for (i = 0; i < g_nTotPins; i++)
  {
    if (g_attachedPin[i] == S_YES)
    {
      // x_pinDigValue[i] = x_pinScenario[i][g_curStep];
      x_pinMode[i]     = g_interruptType[i];
      g_doInterrupt    = S_YES;
    }
  }
}

void showError(const char *m, int value)
//====================================
{
  char err_msg[300];
  strcpy(err_msg,"SimuinoERROR: ");
  strcat(err_msg,m);
  fprintf(stderr,"%s %d\n",err_msg,value);
  error = 1;
}

//====================================
void errorLog(const char msg[], int x)
//====================================
{
  showError(msg,x);
}
//====================================


//====================================
void writeRegister(int digital, int reg, int port, int value)
//====================================
{

  //-------------------------------------------------------
  if (reg == R_PORT && digital == 1) // 0=LOW 1=HIGH
  {
    if (port <= 7  && port >=  0)bitWrite(&PORTD, port, value);
    if (port >= 8  && port <= 15)bitWrite(&PORTB, port - 8, value);
    if (port >= 16 && port <= 23)bitWrite(&PORTE, port - 16, value);
    if (port >= 24 && port <= 31)bitWrite(&PORTF, port - 24, value);
    if (port >= 32 && port <= 39)bitWrite(&PORTK, port - 32, value);
    if (port >= 40 && port <= 47)bitWrite(&PORTL, port - 40, value);
    if (port >= 48 && port <= 55)bitWrite(&PORTM, port - 48, value);
  }
  if (reg == R_PORT && digital == 0)
  {
    if (port <=  7 && port >=  0)bitWrite(&PORTC, port, value);
    if (port <= 15 && port >=  8)bitWrite(&PORTN, port - 8, value);
  }
  //-------------------------------------------------------
  if (reg == R_DDR && digital == 1) // 0=INPUT 1=OUTPUT
  {
    if (port <= 7 && port >=  0)bitWrite(&DDRD, port, value);
    if (port >= 8 && port <= 13)bitWrite(&DDRB, port - 8, value);
    if (port >= 16 && port <= 23)bitWrite(&DDRE, port - 16, value);
    if (port >= 24 && port <= 31)bitWrite(&DDRF, port - 24, value);
    if (port >= 32 && port <= 39)bitWrite(&DDRK, port - 32, value);
    if (port >= 40 && port <= 47)bitWrite(&DDRL, port - 40, value);
    if (port >= 48 && port <= 55)bitWrite(&DDRM, port - 48, value);
  }
  if (reg == R_DDR && digital == 0)
  {
    if (port <=  7 && port >=  0)bitWrite(&DDRC, port, value);
    if (port <= 15 && port >=  8)bitWrite(&DDRN, port - 8, value);
  }
  //-------------------------------------------------------
  if (reg == R_PIN && digital == 1) // 0=INPUT 1=OUTPUT
  {
    if (port <= 7 && port >=  0)bitWrite(&PIND, port, value);
    if (port >= 8 && port <= 13)bitWrite(&PINB, port - 8, value);
    if (port >= 16 && port <= 23)bitWrite(&PINE, port - 16, value);
    if (port >= 24 && port <= 31)bitWrite(&PINF, port - 24, value);
    if (port >= 32 && port <= 39)bitWrite(&PINK, port - 32, value);
    if (port >= 40 && port <= 47)bitWrite(&PINL, port - 40, value);
    if (port >= 48 && port <= 55)bitWrite(&PINM, port - 48, value);
  }
  if (reg == R_PIN && digital == 0)
  {
    if (port <=  7 && port >=  0)bitWrite(&PINC, port, value);
    if (port <= 15 && port >=  8)bitWrite(&PINN, port - 8, value);
  }
  //-------------------------------------------------------

}

//====================================
int readRegister(int reg, int port)
//====================================
{
  int value = 99, pin;

  //-------------------------------------------------------
  if (reg == R_PORT && port < g_nDigPins) // 0=LOW 1=HIGH
  {
    if (port >=  0 && port <=  7)value = bitRead(PORTD, port);
    if (port >=  8 && port <= 15)value = bitRead(PORTB, port - 8);
    if (port >= 16 && port <= 23)value = bitRead(PORTE, port - 16);
    if (port >= 24 && port <= 31)value = bitRead(PORTF, port - 24);
    if (port >= 32 && port <= 39)value = bitRead(PORTK, port - 32);
    if (port >= 40 && port <= 47)value = bitRead(PORTL, port - 40);
    if (port >= 48 && port <= 55)value = bitRead(PORTM, port - 48);
  }
  if (reg == R_PORT && port >= g_nDigPins) // Analog Pins
  {
    pin = port - g_nDigPins;
    if (pin <=  7 && pin >=  0)value = bitRead(PORTC, pin);
    if (pin <= 15 && pin >=  8)value = bitRead(PORTN, pin - 8); // verify
  }
  //-------------------------------------------------------
  if (reg == R_DDR && port < g_nDigPins) // 0=INPUT 1=OUTPUT
  {
    if (port <=  7 && port >=  0)value = bitRead(DDRD, port);
    if (port >=  8 && port <= 15)value = bitRead(DDRB, port - 8);
    if (port >= 16 && port <= 23)value = bitRead(DDRE, port - 16);
    if (port >= 24 && port <= 31)value = bitRead(DDRF, port - 24);
    if (port >= 32 && port <= 39)value = bitRead(DDRK, port - 32);
    if (port >= 40 && port <= 47)value = bitRead(DDRL, port - 40);
    if (port >= 48 && port <= 55)value = bitRead(DDRM, port - 48);
  }
  if (reg == R_DDR && port >= g_nDigPins) // Analog Pins
  {
    pin = port - g_nDigPins;
    if (pin <=  7 && pin >=  0)value = bitRead(DDRC, pin);
    if (pin <= 15 && pin >=  8)value = bitRead(DDRN, pin - 8); // verify
  }
  //-------------------------------------------------------
  if (reg == R_PIN && port < g_nDigPins) // 0=INPUT 1=OUTPUT
  {
    if (port <=  7 && port >=  0)value = bitRead(PIND, port);
    if (port >=  8 && port <= 15)value = bitRead(PINB, port - 8);
    if (port >= 16 && port <= 23)value = bitRead(PINE, port - 16); // verify
    if (port >= 24 && port <= 31)value = bitRead(PINF, port - 24); // verify
    if (port >= 32 && port <= 39)value = bitRead(PINK, port - 32); // verify
    if (port >= 40 && port <= 47)value = bitRead(PINL, port - 40); // verify
    if (port >= 48 && port <= 55)value = bitRead(PINM, port - 48); // verify
  }
  if (reg == R_PIN && port >= g_nDigPins) // Analog Pins
  {
    pin = port - g_nDigPins;
    if (pin <=  7 && pin >=  0)value = bitRead(PINC, pin);
    if (pin <= 15 && pin >=  8)value = bitRead(PINN, pin - 8); // verify
  }
  //-------------------------------------------------------

  return (value);
}

//====================================
void updateFromRegister()
//====================================
{
  int i;

  for (i = 0; i < g_nTotPins; i++)
  {
    // Pin Mode
    x_pinMode[i] = readRegister(R_DDR, i);

    // Pin Value Output
    if (x_pinMode[i] == OUTPUT)
      x_pinDigValue[i] = readRegister(R_PORT, i);

    // Pin Value Input
    if (x_pinMode[i] != OUTPUT)
      x_pinDigValue[i] = readRegister(R_PIN, i);
  }


}



void doInterrupt(int pin, int ir, int irType, int value)
//====================================
{

  if (g_ongoingInterrupt == S_YES || g_allowInterrupt == S_NO)
  {
    errorLog("Try to interrupt during ongoing interrupt", g_curStep);
    return;
  }

  g_ongoingInterrupt = S_YES;
  interrupt[ir]();
  g_ongoingInterrupt = S_NO;

}

//====================================
void interruptNow()
//====================================
{
  int ir, ir_1, ir_2, pin, extTrigged = S_NO;

  for (ir = 0; ir <= max_irPin; ir++)
  {

    if (attached[ir] == S_YES)
    {
      pin = inrpt[ir];

      // ir_1 = getDigitalPinValue(pin, g_curStep);
      // ir_2 = getDigitalPinValue(pin, g_curStep - 1);


      if (interruptMode[ir] == RISING && ir_1 == 1 && ir_2 == 0)
      {
        doInterrupt(pin, ir, RISING, 1);
      }
      if (interruptMode[ir] == FALLING && ir_1 == 0 && ir_2 == 1)
      {
        doInterrupt(pin, ir, FALLING, 0);
      }
      if (interruptMode[ir] == CHANGE && ir_1 != ir_2)
      {
        doInterrupt(pin, ir, CHANGE, ir_1);
      }
      if (interruptMode[ir] == LOW && ir_1 != ir_2)
      {
        doInterrupt(pin, ir, LOW, ir_1);
      }
    }
  }
}

//====================================
// End of file
//====================================
