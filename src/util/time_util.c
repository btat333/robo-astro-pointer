#include <time.h>

#include "time_util.h"

// Unix Time to Julian Date Function
//
// Supports to integer seconds
double get_julian_date(time_t unix_seconds)
{
   return ( unix_seconds / 86400.0 ) + 2440587.5;
}