#ifndef STRUCTURES_H
#define STRUCTURES_H

// For anything which doesn't fit in other structs
typedef struct AC_Options {

} AC_Options;

// Physical properties of the system
typedef struct AC_System{
  unsigned int nx, ny, n_tot;
  double x_spacing, y_spacing;
  double approach;
  double* height;
  double* pressure;  
  double* kernel;
} AC_System;

#endif
