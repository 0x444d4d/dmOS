#include "conversion.h"

unsigned int bcd_to_dec ( unsigned int value ) {
    return value = ((value / 16) * 10 + (value % 16));
}
