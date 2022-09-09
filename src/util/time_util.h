
#ifndef __TIMEUTIL_H_INCLUDED__
#define __TIMEUTIL_H_INCLUDED__

#include <time.h>

// UTC to UT1 Time Function
// TODO: Correct for UTC/UT1 offset

// Unix Time to Julian Date Function
//
// Supports to integer seconds
double get_julian_date(time_t unix_seconds);


#endif  //  __TIMEUTIL_H_INCLUDED__