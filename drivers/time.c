#include "time.h"

int time_update_in_progress( void ) {
    write_byte_port( 0x70, 0x0A | 0x01 << 7 );
    return ( read_byte_port( 0x71 ) & 0x80 );
}

void delay( short unsigned seconds_to_wait ) {
    time_date time_s, new_time_s;

    //To ensure we wait AT LEAST "seconds_to_wait" amount of seconds,
    //wait until the next time update has finished.
    while ( time_update_in_progress() != 1 );
    while ( time_update_in_progress() != 0 );

    //Now we get the current time (time_s) and new_time_s which will be compared
    //to time_s.
    get_time( time_s );
    get_time( new_time_s );

    //If "seconds_to_wait" seconds have passed -> return;
    while ( ( new_time_s.second - time_s.second ) < seconds_to_wait ) {
        get_time( new_time_s );
    }
}

void get_time( time_date time_s ) {
    unsigned i = 0;

    while ( time_update_in_progress() != 0 );


    write_byte_port( 0x70, 0x00 | 0x01 << 7);
    time_s.second = read_byte_port( 0x71 );
    write_byte_port( 0x70, 0x02 | 0x01 << 7);
    time_s.minute = read_byte_port( 0x71 );
    write_byte_port( 0x70, 0x04 | 0x01 << 7);
    time_s.hour = read_byte_port( 0x71 );
    write_byte_port( 0x70, 0x07 | 0x01 << 7);
    time_s.day = read_byte_port( 0x71 );
    write_byte_port( 0x70, 0x08 | 0x01 << 7);
    time_s.month = read_byte_port( 0x71 );
    write_byte_port( 0x70, 0x09 | 0x01 << 7);
    time_s.year = read_byte_port( 0x71 );

}
