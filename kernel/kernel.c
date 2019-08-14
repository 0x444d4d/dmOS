#define NULL 0x00

void itos( int value, char* string );

#include "definitions.h"
#include "../drivers/ports.h"
#include "../drivers/vga.h"
#include "../drivers/time.h"


void main () {
    char bar[10] = "======\0";
    char helloworld[50] = "dmOS\0";
    char pressEnter[50] = "Press Enter to continue\0";
    char second[4] = "NaN";
    time_date time_s;
    unsigned char test = 21;

    initVideo(); //Initialize VGA output;

    printString( bar, 37, 11 );
    printString( helloworld, 38, 12 );
    printString( bar, 37, 13 );
    printString( pressEnter, 0, 0 );

    while( 1 ) {
        printString( pressEnter, 0, 1 );
        ++pressEnter[0];
        get_time( time_s );
        itos( time_s.second, second );
        printString( second, 39, 16 );
    }

    set_cursor( 23, 15 );

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
