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
using namespace std;
#include "common.h"
#include <mutex>
#include "global_variables.h"

//===================================
// Simulator status
int x_pinValue[MAX_TOTAL_PINS];
int x_leds[25] = {0};
int x_pinMode[MAX_TOTAL_PINS];
int x_pinScenario[MAX_TOTAL_PINS][SCEN_MAX];
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


char  sketch[120], g_temp[120];
int   g_simulationLength = 111;
char  g_version[40];



void  stepCommand();

int   row, col;
int   graph_x = 10, graph_y = 10;

char  appName[120];




int   anaPinPos[MAX_PIN_ANALOG_MEGA];
int   c_analogPin[MAX_PIN_ANALOG_MEGA];
int   s_analogPin[SCEN_MAX][MAX_PIN_ANALOG_MEGA];
int   s_analogStep[SCEN_MAX][MAX_PIN_ANALOG_MEGA];

int   digPinPos[MAX_PIN_DIGITAL_MEGA];
int   c_digitalPin[MAX_PIN_DIGITAL_MEGA];
int   s_digitalPin[SCEN_MAX][MAX_PIN_DIGITAL_MEGA];
int   s_digitalStep[SCEN_MAX][MAX_PIN_DIGITAL_MEGA];
int   digitalMode[MAX_PIN_DIGITAL_MEGA];

int   s_interrupt[SCEN_MAX][MAX_PIN_IR_MEGA];
int   s_interruptStep[SCEN_MAX];
int   interruptMode[MAX_PIN_IR_MEGA];

char  textPinModeIn[MAX_PIN_DIGITAL_MEGA][SIZE_ROW];
char  textPinModeOut[MAX_PIN_DIGITAL_MEGA][SIZE_ROW];
char  textDigitalWriteLow[MAX_PIN_DIGITAL_MEGA][SIZE_ROW];
char  textDigitalWriteHigh[MAX_PIN_DIGITAL_MEGA][SIZE_ROW];
char  textAnalogWrite[MAX_PIN_DIGITAL_MEGA][SIZE_ROW];
char  textAnalogRead[MAX_PIN_ANALOG_MEGA][SIZE_ROW];
char  textDigitalRead[MAX_PIN_DIGITAL_MEGA][SIZE_ROW];

int   stepAtReadD[MAX_READ];
int   stepAtReadA[MAX_READ];
int   valueAtReadD[MAX_READ];
int   valueAtReadA[MAX_READ];
int   pinAtReadD[MAX_READ];
int   pinAtReadA[MAX_READ];

int   paceMaker = 0;
int   baud = 0;
int   error = 0;
int   logging = S_NO;
int   serialSize = 1;
int   serialMode = S_OFF;
int   scenAnalog    = 0;
int   scenDigital   = 0;
int   scenInterrupt = 0;

int   conn;

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


int nCodeString = 0;
int default_sim_length = 50;


FILE *s_log, *e_log, *c_log, *a_log, *u_log, *x_log, *t_log, *r_log;
FILE *f_event, *f_cust, *f_serial, *f_time, *f_ino;
FILE *f_pinmod, *f_digval, *f_anaval, *f_pinrw;


#include "arduino.h"
#include "code.h"
#include "common_lib.c"
#include "servuino.h"
#include "servuino_lib.c"
#include "arduino_lib.c"
#include "Esplora.c"

#include "sketch/sketch.ino"

bool running = true;

// void setup();
// void loop();

//====================================
void runEncoding(int n)
//====================================
{
  int i;


  g_curStep = 0;
  setup();
  increment_counter(1032);

  while(running) {
    g_curLoop++;
    loop();
  }
}


//=======================R=============
int run_servuino()
//====================================
{
  int x, i;


  g_nTotPins = setRange(g_boardType);
  if (g_boardType == UNO)g_nDigPins = MAX_PIN_DIGITAL_UNO;
  if (g_boardType == MEGA)g_nDigPins = MAX_PIN_DIGITAL_MEGA;

  //boardInit();
  //readCustom(); // Get customized log text from sketch
    g_simulationLength = default_sim_length;
    g_scenSource = 0;
    runEncoding(g_simulationLength);
  return EXIT_SUCCESS;
}

