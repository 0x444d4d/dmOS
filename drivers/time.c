#include "time.h"

int time_update_in_progress( void ) {
    write_byte_port( 0x70, 0x0A );
    return ( read_byte_port( 0x71 ) & 0x80 );
}


void delay( short unsigned seconds_to_wait ) {
    time_date time_s, new_time_s;
    //wait until the next time update has finished.
    while ( time_update_in_progress() != 0 );

    //Now we get the current time (time_s) and new_time_s which will be compared
    //to time_s.
    time_s = get_time();
    new_time_s = get_time();

    //If "seconds_to_wait" seconds have passed -> return;
    while ((( time_s.second + seconds_to_wait ) % 60 ) < new_time_s.second) {
        new_time_s = get_time();
    }
}

time_date get_time( void ) {
    unsigned i = 0;
    time_date time_s;

    while ( time_update_in_progress() == 1 );

    write_byte_port( 0x70, 0x00 );
    time_s.second = read_byte_port( 0x71 );
    write_byte_port( 0x70, 0x02 );
    time_s.minute = read_byte_port( 0x71 );
    write_byte_port( 0x70, 0x04 );
    time_s.hour = read_byte_port( 0x71 );
    write_byte_port( 0x70, 0x07 );
    time_s.day = read_byte_port( 0x71 );
    write_byte_port( 0x70, 0x08 );
    time_s.month = read_byte_port( 0x71 );
    write_byte_port( 0x70, 0x09 );
    time_s.year = read_byte_port( 0x71 );

    return time_s;
}
