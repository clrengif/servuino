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


//=====================================
// Functions
//=====================================

//------ Digital I/O -----------------------

void pinMode(int pin, int mode)
{
//  increment_counter(20);
  if (mode == INPUT)
    cout << "doing input pinmode" << endl;
  if (mode == OUTPUT)
    cout << "doing output pinmode" << endl;
  
}
void digitalWrite(int pin, int value)
{
//  increment_counter(20);
  if (value == 0)
    cout << "doing digitalWrite low" << endl;
  if (value == 1)
    cout << "doing digitalWrite high" << endl;
  
}
int digitalRead(int pin)
{
//  increment_counter(20);
    cout << "doing digitalRead" << endl;
    return -9;
}

void analogWrite(int pin, int value) //PWM
{
//  increment_counter(20);
    cout << "doing analogWrite" << endl;
  
}

int analogRead(int pin)
{
//  increment_counter(20);
  pin = g_nDigPins + pin;
    cout << "doing analogRead" << endl;
  return 0;
}

//------ Advanced I/O ----------------------
void tone(int pin, unsigned int freq)
{
}

void tone(int pin, unsigned int freq, unsigned long duration)
{
}

void noTone(int pin)
{
}

void shiftOut(int dataPin, int clockPin, int bitOrder, int value)
{
  //bitOrder: which order to shift out the bits; either MSBFIRST or LSBFIRST.
}

int shiftIn(int dataPin, int clockPin, int bitOrder)
{
  //bitOrder: which order to shift out the bits; either MSBFIRST or LSBFIRST.
  return -9;
}

unsigned long pulseIn(int pin, int value)
{
  return -9;
}

unsigned long pulseIn(int pin, int value, unsigned long timeout)
{
  return -9;
}

//------ Time ------------------------------

unsigned long millis()
{
//  increment_counter(1);
  return (g_curStep * 100);
}

unsigned long micros()
{
//  increment_counter(1);
  return (g_curStep * 100000);
}

void delay(int ms)
{
//  increment_counter(ms*1000);
  
}

void delayMicroseconds(int us)
{
//  increment_counter(us);
  
}

//------ Math ------------------------------
void test_math()
{
  double r, x, z;
  int y;
  y = min(1, 2);
  y = max(1, 2);
  y = abs(1);
  r = pow(x, z);
  r = sqrt(y);
}


int map(int x, int fromLow, int fromHigh, int toLow, int toHigh)
{
//  increment_counter(100);
  int y;
  y = (float)(x - fromLow) / (fromHigh - fromLow) * (toHigh - toLow) + toLow;
  //printf("%d %d\n",x,y);
  return (y);
}


//------ Trigonometry ----------------------
void test_trigonometry()
{
  double x;
  x = sin(1);
  x = cos(1);
  x = tan(1);
}
//------ Random Numbers --------------------
void randomSeed(int seed)
{
//  increment_counter(100);
  srand(seed);
}

long random(long upperLimit)
{
//  increment_counter(100);
  long x = RAND_MAX / upperLimit;
  x = long(rand() / x);
  return (x);
}

long random(long lowerLimit, long upperLimit)
{
//  increment_counter(100);
  long interval, temp = 0;
  if (lowerLimit < upperLimit)
  {
    interval = upperLimit - lowerLimit;
    temp = lowerLimit + random(interval);
  }
  return (temp);
}


//------ Bits and Bytes --------------------
unsigned char lowByte(int x)
{
//  increment_counter(100);
  return (x & 0xff);
}

unsigned char highByte(int x)
{
//  increment_counter(100);
  unsigned char y;
  x = x & 0xff00;
  y = x >> 8;
  return (y);
}

int bitRead(int x, int n)
{
//  increment_counter(100);
  int bit;
  //printf("bitRead: x=%d n=%d PORTB=%d\n",x,n,PORTB);
  bit = x >> n;
  bit = bit & 0x0001;
  //printf("bitRead: x=%d n=%d PORTB=%d bit=%d\n",x,n,PORTB,bit);
  return (bit);
}

void  bitSet(unsigned int *x, int n)
{
//  increment_counter(100);
  int res, mask;

  mask = 1 << n;
  *x  = *x | mask;
}

void bitClear(unsigned int *x, int n)
{
//  increment_counter(100);
  int res, mask;

  mask = 1 << n;
  *x  = *x & ~mask;
}

void bitWrite(unsigned int *x, int n, int b)
{
//  increment_counter(100);
  //printf("bitWrite: %d %d %d PORTB=%d\n",*x,n,b,PORTB);
  if (b == 0)bitClear(x, n);
  if (b == 1)bitSet(x, n);
  
}

int bit(int n)
{
  int res;
  res = 1 << n;
  return (res);
}


//------ External Interrupts ---------------


void attachInterrupt(int ir, void(*func)(), int mode)
{
//  increment_counter(100);
  int pin, ok = S_NOK;

  ok = checkRange(S_OK, "interrupt", ir);

  if (ok == S_OK)
  {

    pin                 = inrpt[ir];

    if (mode == LOW)
      cout << "attach interrupt low" << endl;
    if (mode == RISING)
      cout << "attach interrupt rising" << endl;
    if (mode == FALLING)
      cout << "attach interrupt falling" << endl;
    if (mode == CHANGE)
      cout << "attach interrupt change" << endl;

    interruptMode[ir] = mode;
    attached[ir]      = S_YES;
    interrupt[ir]     = func;

    //interrupt[ir](); ????

    g_attachedPin[pin]  = S_YES;
    g_interruptType[pin] = mode;

    digitalMode[pin]  = mode;
  }
  else
  {
    errorLog("attachInterruptERROR", ir);
  }

  
}


//---------------------------------------------------
void detachInterrupt(int ir)
{
//  increment_counter(100);
  int ok = S_NOK, pin;


  ok = checkRange(S_OK, "interrupt", ir);
  if (ok == S_OK)
  {
    //interrupt[ir]     = NULL;
    attached[ir]      = S_NO;
    pin               = inrpt[ir];
    g_attachedPin[pin] = S_NO;
    digitalMode[pin]  = INPUT;
  }

  
}
//------ Interrupts ------------------------
void interrupts()
{
}
void noInterrupts()
{
}
//------ Communication ---------------------




void serial::begin(int baudRate)
{
  digitalMode[0] = RX;
  digitalMode[1] = TX;

  
}

void serial::end()
{
  digitalMode[0] = FREE;
  digitalMode[1] = FREE;

  
}

int serial::available()  // returns the number of bytes available to read
{
//  increment_counter(12);
  return (1);
}

char serial::read() // the first byte of incoming serial data available (or -1 if no data is available)
{
//  increment_counter(100);
  return (-1);
}

int serial::peek()
{
//  increment_counter(100);
  return (-1);
}

void serial::flush()
{
//  increment_counter(100);
}

void serial::print(int x)
{
//  increment_counter(100);
  
}

void serial::print(int x, int base)
{
//  increment_counter(16);
  
}

void serial::print(const char *p)
{
//  increment_counter(100);
  
}

void serial::print(unsigned char uc)
{
//  increment_counter(100);
  
}


void serial::println(int x)
{
//  increment_counter(100);
  
}

void serial::println(const char *p)
{
//  increment_counter(100);
  
}

void serial::println(string s)
{
//  increment_counter(100);
  const char *p;
  p = s.c_str();
  
}

void serial::println(String s)
{
//  increment_counter(100);
  const char *p;
  p = s.getPointer();
  
}
void serial::println()
{
//  increment_counter(100);
}

void serial::println(unsigned char uc)
{
//  increment_counter(100);
}

void serial::write(char *p)
{
//  increment_counter(100);
}


//==========================================
// String
//==========================================

// conversion (and default) constructor converts char * to String
String::String( const char *s )
  : lngth( ( s != 0 ) ? strlen( s ) : 0 )
{
//  increment_counter(100);
  //cout << "Conversion (and default) constructor: " << s << endl;
  setString( s ); // call utility function
}

// copy constructor
String::String( const String &copy )
  : lngth( copy.lngth )
{
//  increment_counter(100);
  //cout << "Copy constructor: " << copy.sPtr << endl;
  setString( copy.sPtr ); // call utility function
}

// Destructor
String::~String()
{
  //cout << "Destructor: " << sPtr << endl;
  delete [] sPtr; // release pointer-based string memory
}

// overloaded = operator; avoids self assignment
const String &String::operator=( const String &right )
{
  //cout << "operator= called" << endl;

  if ( &right != this ) // avoid self assignment
  {
    delete [] sPtr; // prevents memory leak
    lngth = right.lngth; // new String length
    setString( right.sPtr ); // call utility function
  } // end if
  else
    cout << "Attempted assignment of a String to itself" << endl;

  return *this;
}

// concatenate right operand to this object and store in this object
const String &String::operator+=( const String &right )
{
  size_t newLength = lngth + right.lngth; // new length
  char *tempPtr = new char[ newLength + 1 ]; // create memory

  strcpy( tempPtr, sPtr ); // copy sPtr
  strcpy( tempPtr + lngth, right.sPtr ); // copy right.sPtr

  delete [] sPtr; // reclaim old space
  sPtr = tempPtr; // assign new array to sPtr
  lngth = newLength; // assign new length to length
  return *this; // enables cascaded calls
}

// is this String empty?
bool String::operator!() const
{
  return lngth == 0;
}

// Is this String equal to right String?
bool String::operator==( const String &right ) const
{
  return strcmp( sPtr, right.sPtr ) == 0;
}

// Is this String less than right String?
bool String::operator<( const String &right ) const
{
  return strcmp( sPtr, right.sPtr ) < 0;
}

// return reference to character in String as a modifiable lvalue
char &String::operator[]( int subscript )
{
  // test for subscript out of range
  if ( subscript < 0 || subscript >= lngth )
  {
    cerr << "Error: Subscript " << subscript
         << " out of range" << endl;
    exit( 1 ); // terminate program
  } // end if

  return sPtr[ subscript ]; // non-const  modifiable lvalue
}

// return reference to character in String as rvalue
char String::operator[]( int subscript ) const
{
  // test for subscript out of range
  if ( subscript < 0 || subscript >= lngth )
  {
    cerr << "Error: Subscript " << subscript
         << " out of range" << endl;
    exit( 1 ); // terminate program
  } // end if

  return sPtr[ subscript ]; // returns copy of this element
}

// return a substring beginning at index and of length subLength
String String::operator()( int index, int subLength ) const
{
  // if index is out of range or substring length < 0,
  // return an empty String object
  if ( index < 0 || index >= lngth || subLength < 0 )
    return ""; // converted to a String object automatically

  // determine length of substring
  int len;

  if ( ( subLength == 0 ) || ( index + subLength > lngth ) )
    len = lngth - index;
  else
    len = subLength;

  // allocate temporary array for substring and
  // terminating null character
  char *tempPtr = new char[ len + 1 ];

  // copy substring into char array and terminate string
  strncpy( tempPtr, &sPtr[ index ], len );
  tempPtr[ len ] = '\0';

  // create temporary String object containing the substring
  String tempString( tempPtr );
  delete [] tempPtr;
  return tempString;
}

int String::getLength() const
{
  return lngth;
}

void String::setString( const char *string2 )
{
  sPtr = new char[ lngth + 1 ];

  if ( string2 != 0 )
    strcpy( sPtr, string2 );
  else
    sPtr[ 0 ] = '\0';
}

ostream &operator<<( ostream &output, const String &s )
{
  output << s.sPtr;
  return output;
}

istream &operator>>( istream &input, String &s )
{
  char temp[ 100 ];
  input >> setw( 100 ) >> temp;
  s = temp;
  return input;
}

String String::operator+(String right )
{
  String temp;
  size_t newLength = lngth + right.lngth;
  char *tempPtr = new char[ newLength + 1 ];
  strcpy( tempPtr, sPtr );
  strcpy( tempPtr + lngth, right.sPtr );
  temp.sPtr = tempPtr;
  temp.lngth = newLength;
  return temp;
}

String String::operator+( const int number )
{
  String temp;
  stringstream ss;
  String right;
  ss << number;
  right = ss.str();
  size_t newLength = lngth + right.lngth;
  char *tempPtr = new char[ newLength + 1 ];
  strcpy( tempPtr, sPtr );
  strcpy( tempPtr + lngth, right.sPtr );
  temp.sPtr = tempPtr;
  temp.lngth = newLength;
  return temp;
}

String String::operator+( unsigned long number )
{
  String temp;
  stringstream ss;
  String right;
  ss << number;
  right = ss.str();
  size_t newLength = lngth + right.lngth;
  char *tempPtr = new char[ newLength + 1 ];
  strcpy( tempPtr, sPtr );
  strcpy( tempPtr + lngth, right.sPtr );
  temp.sPtr = tempPtr;
  temp.lngth = newLength;
  return temp;
}

String String::operator+( const char one )
{
  String temp;
  stringstream ss;
  String right;
  ss << one;
  right = ss.str();
  size_t newLength = lngth + right.lngth;
  char *tempPtr = new char[ newLength + 1 ];
  strcpy( tempPtr, sPtr );
  strcpy( tempPtr + lngth, right.sPtr );
  temp.sPtr = tempPtr;
  temp.lngth = newLength;
  return temp;
}


const String &String::operator=( string right )
{
  char *p;
  lngth = right.length();
  p = (char *)(right.c_str());
  setString(p);
  return *this;
}

const String &String::operator=(const char *right )
{
  const char *p;
  lngth = strlen(right);
  p = right;
  setString(p);
  return *this;
}


String::String( const int x )
{
  char p[10];
  sprintf(p, "%d", x);
  lngth = strlen(p);
  setString(p);
}

String::String( const int x, const int base )
{
  char p[10];
  if (base == BIN)sprintf(p, "BIN%d", x);
  if (base == DEC)sprintf(p, "DEC%d", x);
  if (base == HEX)sprintf(p, "HEX%d", x);
  lngth = strlen(p);
  setString(p);
}

char String::charAt( const int n )
{
  char res;
  res = sPtr[n];
  return (res);
}

int String::compareTo( const String s )
{
  int res;
  if (*this > s)res = -1;
  if (*this < s)res = 1;
  if (*this == s)res = 0;
  return (res);
}

String String::concat( const String s )
{
  *this += s;
  return *this;
}

bool String::endsWith( const String s )
{
  bool res;
  int pos;
  string p(sPtr);
  pos = lngth - s.lngth;
  res = p.compare(pos, s.lngth, s.sPtr);
  return (res);
}

bool String::equals( const String s )
{
  return strcmp( sPtr, s.sPtr ) == 0;
}

bool String::equalsIgnoreCase( const String s )
{
  // Not implemented
  return strcmp( sPtr, s.sPtr ) == 0;
}

void String::getBytes( int buf[], int *len )
{
  int i;
  char *p;

  p = sPtr;
  for (i = 0; i < lngth; i++)
  {
    buf[i] = (int) * p; // Issue 14
    p++;
  }
  *len = lngth;
  
}

int String::indexOf(char val)
{
  // Not implemented
  return (-1);
}

int String::indexOf(String val)
{
  // Not implemented
  return (-1);
}

int String::indexOf(char val, int from)
{
  // Not implemented
  return (-1);
}

int String::indexOf(String val, int from)
{
  // Not implemented
  return (-1);
}

int String::lastIndexOf(char val)
{
  // Not implemented
  return (-1);
}

int String::lastIndexOf(String val)
{
  // Not implemented
  return (-1);
}

int String::lastIndexOf(char val, int from)
{
  // Not implemented
  return (-1);
}

int String::lastIndexOf(String val, int from)
{
  // Not implemented
  return (-1);
}

int String::length()
{
  return (lngth);
}

String String::replace(String sub1, String sub2)
{
  // Not implemented
  String res;
  return (res);
}

void String::setCharAt( int index, char c )
{
  // Not implemented
  
}

bool String::startsWith( String s )
{
  bool res;
  // Not implemented
  return (res);
}

String String::substring(int from)
{
  String res;
  // Not implemented
  return (res);
}

String String::substring(int from, int to)
{
  String res;
  // Not implemented
  return (res);
}

void String::toCharArray(char buf[], int *len)
{
  // Not implemented
  
}

void String::toLowerCase()
{
  // Not implemented
  
}

void String::toUpperCase()
{
  // Not implemented
  
}

void String::trim()
{
  // Not implemented
  
}

char* String::getPointer()
{
  return (sPtr);
}

// End of file
