#ifndef STRUCTURES_H
#define STRUCTURES_H

// Everything read from the options file
typedef struct CC_Options {

} CC_Options;

// Physical properties of the system
typedef struct CC_System{
  unsigned int nx, ny, n_tot;
  double x_spacing, y_spacing;
  double approach;
  double radius;
} CC_System;

#endif
