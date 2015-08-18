
int solve(AC_System, double *height){
  
  return 0;
}

int calculate_kernel(AC_System system*, double* kernel){
  double x1, x2, y1, y2, pref;
  int i, j;

  pref = 2.0 / AL_PI;

  for(i = 0; i<system->nx; i++){
    for(j = 0; j<system->ny; j++){
      x1 = system->x_spacing * (i - 0.5);
      x2 = system->x_spacing * (i + 0.5);
      y1 = system->y_spacing * (j - 0.5);
      y2 = system->y_spacing * (j + 0.5);
      kernel[i + system->nx*j] = pref * (kernel_indefinite(x2, y2) - kernel_indefinite(x1, y2) - kernel_indefinite(x2, y1) + kernel_indefinite(x1, y1));
    }
  }
  return 0;
}

double kernel_indefinite(double x, double y){
  return fabs(x) * asinh(y/x) + fabs(y) * asinh(x/y);
}

int spherical_h_profile(AC_System *system, double* init_height){
  int i, j;
  double r2, x, y, inverse_radius;
  double c_x, c_y;

  c_x = system->x_spacing * system->n_x * 0.5; 
  c_y = system->y_spacing * system->n_y * 0.5; 
  inverse_radius = 0.5 / system->radius;

  for (i=0; i<system->nx; i++){
    for (j=0; j<system->ny; j++){
      x = (i * system->x_spacing) - c_x; 
      y = (j * system->y_spacing) - c_y;
      r2 = x*x + y*y;
      height[i + j * system->nx] = r2 * inverse_radius;
    }
  }

  return 0;
}

