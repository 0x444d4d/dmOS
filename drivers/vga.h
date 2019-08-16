#ifndef VGA
#define VGA
void clear ( void );
void printChar( void );
void updateVideo( void );
void initVideo( void );
void updateVideo( void );
void printString( char string[], unsigned char x, unsigned char y );
void print_binary_byte( char value, unsigned char x, unsigned char y );
void print_binary_word( short value, unsigned char x, unsigned char y );
void print_binary_double( long value, unsigned char x, unsigned char y );
short unsigned get_cursor( void );
void set_cursor( unsigned char x, unsigned char y );
#endif
