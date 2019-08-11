
unsigned char read_byte_port( short unsigned port ) {
    unsigned char result;

    __asm__ ("in %%dx, %%al" : "=a"(result) : "d" (port)); 
    return result;
}

void write_byte_port( short unsigned port, unsigned char byte ) {
    __asm__ ("out %%al, %%dx" :: "a" (byte), "d" (port));
}


unsigned char read_word_port( short unsigned port ) {
    unsigned short result;

    __asm__ ( "in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void write_word_port( short unsigned port, short unsigned word ) {
    __asm__ ( "out %%ax, %%dx" : : "a" (word), "d" (port));
}

