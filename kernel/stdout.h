#ifndef STDOUT
#define STDOUT
void printChar( void );
void updateVideo( void );
void initVideo( void );
void updateVideo( void );
void printString( char string[],  short unsigned x, short unsigned y );
short unsigned get_cursor( void );
void set_cursor( unsigned char x, unsigned char y );
#endif
