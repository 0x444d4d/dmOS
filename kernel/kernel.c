#define NULL 0x00

#include "definitions.h"
#include "../drivers/ports.h"
#include "stdout.h"

void itos( int value, char* string );

void main () {
  char bar[10] = "======\0";
  char helloworld[50] = "dmOS\0";
  char pressEnter[50] = "Press Enter to continue\0";

  initVideo(); //Initialize VGA output;

  printString( bar, 37, 11 );
  printString( helloworld, 38, 12 );
  printString( bar, 37, 13 );
  printString( pressEnter, 0, 0 );

  
  set_cursor( 27, 15 );

}

void itos( int value, char* string ) {
    char aux;
    short unsigned i = 0;

    do {
        string[i++] = (value % 10) + 48;
        value /= 10;
    } while (value > 0);

    string[i] = '\0';
}
