#ifndef PSEC4SIM_H
#define PSEC4SIM_H

#include <string>
#include <iostream>
#include <vector>
#include <time.h>

#include "Tool.h"

#include "TRandom.h"

#include "PSEC4_EVAL.h"

class PSEC4Sim: public Tool {


 public:

  PSEC4Sim();
  bool Initialise(std::string configfile,DataModel &data);
  bool Execute();
  bool Finalise();


 private:

  int num_readouts;
  int trig_mode;
  int acq_rate_hertz;
  int acq_rate_usecs; 
  
};


#endif
