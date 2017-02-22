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

#define LOW    0
#define HIGH   1

#define INPUT  0
#define OUTPUT 1

#define CHANGE  11
#define RISING  12
#define FALLING 13


#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#define _BV(bit) (1 << (bit))

#include "binary.h"

//typedef int byte;
typedef uint8_t byte;
typedef int word;
typedef bool boolean;


// Functions
int   bitRead(int x, int n);
void  bitSet(unsigned int *x, int n);

int A0;
int A1;
int A2;
int A3;
int A4;
int A5;
int A6;
int A7;
int A8;
int A9;
int A10;
int A11;
int A12;
int A13;
int A14;

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


