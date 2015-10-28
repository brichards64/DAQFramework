#ifndef ANALYSEPSEC_H
#define ANALYSEPSEC_H

#include <string>
#include <iostream>

#include "Tool.h"

#include "TTree.h"
#include "TBranch.h"

class AnalysePSEC: public Tool {


 public:

  AnalysePSEC();
  bool Initialise(std::string configfile,DataModel &data);
  bool Execute();
  bool Finalise();


 private:

  double threshold;

  TTree* cosmics;
  TTree* events;

  float in,out;

  float c0,c1,c2,c3,c4,c5;
  int r0,r1,r2,r3,r4,r5;
  
  TBranch        *b_c0; 
  TBranch        *b_c1; 
  TBranch        *b_c2; 
  TBranch        *b_c3; 
  TBranch        *b_c4; 
  TBranch        *b_c5; 
  TBranch        *b_r0; 
  TBranch        *b_r1;  
  TBranch        *b_r2; 
  TBranch        *b_r3; 
  TBranch        *b_r4; 
  TBranch        *b_r5; 


};


#endif
