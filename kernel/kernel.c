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

    while ( 1 ) {
        printString( pressEnter, 0, 0 );
        printString( bar, 37, 11 );
        printString( helloworld, 38, 12 );
        printString( bar, 37, 13 );
        ++pressEnter[0];
        time_s = get_time();
        itos( time_s.second, second );
        printString( second, 39, 16 );
        printString( "Valor de second: \0", 0, 17 );
        print_binary_byte( time_s.second, 20, 17 );
        print_binary_double( (unsigned)4, 20, 18 );
    }

    set_cursor( 23, 15 );

}


void itos( int value, char* string ) {
    char aux;
    short unsigned i, j;
    short unsigned size = 0;

    do {
        //convert value to decimal string
        string[size++] = (value % 10) + 48;
        value /= 10;
    } while (value > 0);

    for ( j = 0, i = size - 1; j < i; ++j, --i ) {
        //Reverse the string
        aux = string[j];
        string[j] = string[i];
        string [i] = aux;
    }

    string[size] = '\0';

    if ( value < 0 ) {
        for ( i = size; i >= 0; --i ) {
            string[i] = string[i-1];
        }
        string[0] = '-';
    }

}
