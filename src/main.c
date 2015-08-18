#include <math.h>
#include "structures.h"

#define AL_PI 3.141592653589793238462643


// TODO sort out the maths / nondimensionalism before doing any implementation. Some of the copy pasted functions probably already rely on the nondimensions used for arclength

int main()
{
  AC_Options options;
  AC_System system;
  void* solver_options;
  
  // Variables for using getopt to parse argv
  int opt, long_index, file_flag = 0;
  char filename[FNAME_MAX];
  size_t filename_length;
  char opt_string[OPT_MAX];
  struct option long_options[] = {
    {"file",    required_argument,  0,  'f' },
    {0,         0,                  0,  0   }
  };
  int num_poss_opts = (sizeof long_options / sizeof (struct option)) - 1;
  
  getOptionString(opt_string, long_options, num_poss_opts);

  while ((opt = getopt_long(argc, argv, (const char*) opt_string, long_options, &long_index)) != -1) {
    switch (opt) {
      case 'f':
        filename_length = strlen(optarg);
        if (filename_length < FNAME_MAX){
          strcpy(filename, optarg);
          file_flag = 1;
        }
        else 
          checkError(FNAME_TOO_LONG);
        break;
      case '?':
        break;
      default:
        //print_usage();
        break;
    }
  }

  // read input file
  // construct structs
  // solve system
  // clean up

  return 0;
}

/* makes the string used by getopt_long to say which options are being used */
int getOptionString(char *opt_string, struct option *long_options, int num_poss_opts){

  int ctr_poss_opts;
  char tmp;
  int has_arg;
  int ctr_pos;

  ctr_pos = 0;
  for (ctr_poss_opts = 0 ; ctr_poss_opts < num_poss_opts ; ctr_poss_opts++){
    tmp = (char)(long_options[ctr_poss_opts].val);

    has_arg = long_options[ctr_poss_opts].has_arg;
    opt_string[ctr_pos] = tmp;
    ctr_pos++;
    if(required_argument == has_arg){
      opt_string[ctr_pos] = ':';
      ctr_pos++;
    }
    else if (optional_argument == has_arg){
      opt_string[ctr_pos] = ';'; 
      ctr_pos++;
    }  
  }
  opt_string[ctr_pos] = '\0';
  return 0;  
}


