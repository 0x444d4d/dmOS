#define VIDEO  0xb8000
#define NVPAGES 5
#define WHITEONBLACK 0x0f
#define VGA_PORT 0x3d4

#include "../kernel/definitions.h"

typedef struct videoBuffer {
  char character[(80*25) * NVPAGES];
  char colour[(80*25) * NVPAGES];
  short unsigned pos;
  char page;

} videoBuffer;

videoBuffer buffer;

void updateVideo ( void ) {
    unsigned i;
    char *videomem = (char*) VIDEO;
    for ( i = 0; i < (80*25); ++i ) {
        *(videomem) = buffer.character[i];
        ++videomem;
        *(videomem)= buffer.colour[i];
        ++videomem;
    }
}

void printString ( char string[], short unsigned x, short unsigned y ) {
    unsigned i, base;
    unsigned size = 0;
    char string_cpy[256];

    for ( i = 0; i < 256; ++i) {
        string_cpy[i] = string[i];
        if (string_cpy[i] != '\0') size++;
        else break;
    }

    base = x+(y*80);
    for ( i = 0; i < size; i++ )
        buffer.character[i + base] = string_cpy[i];

    updateVideo();
}

void printBinChar( char value, unsigned char x, unsigned char y ) {
    char string[9] = "\0";

    string[0] = (value & 0x80) ? 49 : 48;
    string[1] = (value & 0x40) ? 49 : 48;
    string[2] = (value & 0x20) ? 49 : 48;
    string[3] = (value & 0x10) ? 49 : 48;
    string[4] = (value & 0x08) ? 49 : 48;
    string[5] = (value & 0x04) ? 49 : 48;
    string[6] = (value & 0x02) ? 49 : 48;
    string[7] = (value & 0x01) ? 49 : 48;
    string[9] = '\0';

    printString( string, x, y );
}

void clear ( void ) {
    short unsigned i;

    for ( i = 0; i < 80*25; ++i ) {
        buffer.character[i] = NULL;
    }
    updateVideo();
}


short unsigned get_cursor( void ) {
    short unsigned cursor;

    write_byte_port(0x3d4, 14);
    buffer.pos = read_byte_port(0x3d5);
    buffer.pos = buffer.pos << 8;
    write_byte_port(0x3d4, 15);
    buffer.pos += read_byte_port(0x3d5);

    return cursor;
}

void set_cursor( unsigned char x, unsigned char y ) {

    short unsigned base = x+(y*80);
    write_byte_port(0x3d4, 14);
    write_byte_port( 0x3d5, (base >> 8) );
    write_byte_port(0x3d4, 15);
    write_byte_port( 0x3d5, base );
}

void initVideo ( void ) {
    unsigned i = 0;

    while (i < (80 * 25) *NVPAGES ) {
        buffer.character[i] = NULL;
        buffer.colour[i] = 0x0f;
        ++i;
    }

    buffer.page = 0;
    set_cursor( 0, 0 );
    buffer.pos = 0;//get_cursor();

    updateVideo();
}
