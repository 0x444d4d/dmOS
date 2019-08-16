#ifndef TIME
#define TIME

typedef struct time_date {
    unsigned char second;
    unsigned char minute;
    unsigned char hour;
    unsigned char day;
    unsigned char month;
    short unsigned year;

} time_date;


int time_update_in_progress( void );
void delay( short unsigned seconds_to_wait );
time_date get_time();

#endif
