
#ifndef __MODELS_H_INCLUDED__
#define __MODELS_H_INCLUDED__

struct GPSPointSolution {
  float latitude; // Assumes north for now [dd][mm.mmmm]
  float longitude; // Assumes west for now [ddd][mm.mmmm]
  float altitude; // meters above sea level
  float hdop; // Accuracy of measurement horizontally - <1 is amazing, 1-5 is great/good
  int sat_num; // number of visible gps satellites.  less than 4 is bad.
};

/* Produces a struct from the gps point solution message */
struct GPSPointSolution parse_gps (char *msg);

#endif  //  __MODELS_H_INCLUDED__