#ifndef PSEC4READER_H
#define PSEC4READER_H

#include <string>
#include <iostream>
#include <vector>
#include <math.h> 

#include "Tool.h"

#include "PSEC4_EVAL.h"

class PSEC4Reader: public Tool {


 public:

  PSEC4Reader();
  bool Initialise(std::string configfile,DataModel &data);
  bool Execute();
  bool Finalise();


 private:

  PSEC4_EVAL command;

  int num_readouts;
  int trig_mode;
  int acq_rate_hertz;
  int acq_rate_usecs; 
  
};


#endif
