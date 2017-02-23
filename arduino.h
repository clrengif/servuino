#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

#include <iomanip>
using std::setw;

#include <cstring> 
using std::strcmp;
using std::strcpy;
using std::strcat;

#include <string> 
using std::string;

#include <cstdlib>
using std::exit;

#include <sstream>
using std::stringstream;

#include <cstdint>


#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3


#define _BV(bit) (1 << (bit))

#include "binary.h"

typedef uint8_t byte;
typedef unsigned int word;
typedef bool boolean;

// #define min(a,b) ((a)<(b)?(a):(b))
// #define max(a,b) ((a)>(b)?(a):(b))
// #define abs(x) ((x)>0?(x):-(x))
// #define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
// #define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
// #define sq(x) ((x)*(x))


// Functions
int   bitRead(int x, int n);
void  bitSet(unsigned int *x, int n);


unsigned int PORTA=0,PORTB=0,PORTC=0,PORTD=0,PORTE=0,PORTF=0,PORTG=0;
unsigned int PORTH=0,PORTJ=0,PORTK=0,PORTL=0,PORTM=0,PORTN=0;

unsigned int DDRA=0,DDRB=0,DDRC=0,DDRD=0,DDRE=0,DDRF=0,DDRG=0;
unsigned int DDRH=0,DDRJ=0,DDRK=0,DDRL=0,DDRM=0,DDRN=0;

unsigned int PINA=0,PINB=0,PINC=0,PIND=0,PINE=0,PINF=0,PING=0;
unsigned int PINH=0,PINJ=0,PINK=0,PINL=0,PINM=0,PINN=0;



class String
{
   friend ostream &operator<<( ostream &, const String & );
   friend istream &operator>>( istream &, String & );

public:
   String( const char * = "" ); // conversion/default constructor
   String( const String & ); // copy constructor
   ~String(); // destructor

   const String &operator=( const String & ); // assignment operator
   const String &operator+=( const String & ); // concatenation operator

   bool operator!() const; // is String empty?
   bool operator==( const String & ) const; // test s1 == s2
   bool operator<( const String & ) const; // test s1 < s2

   bool operator!=( const String &right ) const
   { 
      return !( *this == right ); 
   } 

   bool operator>( const String &right ) const
   { 
      return right < *this; 
   } 
 
   bool operator<=( const String &right ) const
   { 
      return !( right < *this ); 
   }

   bool operator>=( const String &right ) const
   { 
      return !( *this < right ); 
   } 

   char &operator[]( int ); // subscript operator (modifiable lvalue)
   char operator[]( int ) const; // subscript operator (rvalue)
   String operator()( int, int = 0 ) const; // return a substring
   int getLength() const; // return string length

   // ============ Benny adding =============
   String( const int x ); 
   String( const int x, const int base );
 
   const String &operator=( string right );
   const String &operator=( const char *right );

   String operator+( const int number );
   String operator+( const char one );
   String operator+( unsigned long number );
   String operator+( String right );

   char charAt(const int n);
   int compareTo(const String s);
   String concat(const String s); 	
   bool endsWith(const String s);
   bool equals(const String s);
   bool equalsIgnoreCase(const String s);	
   void getBytes(int buf[], int *len);	
   int indexOf(char val); 
   int indexOf(String val); 
   int indexOf(char val, int from); 
   int indexOf(String val, int from); 
   int lastIndexOf(char val); 
   int lastIndexOf(String val); 
   int lastIndexOf(char val, int from); 
   int lastIndexOf(String val, int from); 
   int length(); 
   String replace(String sub1, String sub2); 
   void setCharAt(int index,char c); 
   bool startsWith(String s); 
   String substring(int from);
   String substring(int from, int to);
   void toCharArray(char buf[], int *len);
   void toLowerCase(); 
   void toUpperCase(); 
   void trim(); 
   char *getPointer(); 

private:
   int lngth; // string length (not counting null terminator)
   char *sPtr; // pointer to start of pointer-based string

   void setString( const char * ); // utility function



}; // end class String



class serial {

 public:
  void begin(int baudRate);
  void end();
  int  available();
  char read();
  int  peek();
  void flush();
  void print(int x);
  void print(int x,int base);
  void print(const char *p);
  void print(unsigned char c);
  void println(int x);
  void println(const char *p);
  void println(string p);
  void println(String p);
  void println();
  void println(unsigned char c);
  void write(char *p);

};
serial Serial,Serial1;


