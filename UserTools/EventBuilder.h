#ifndef EVENTBUILDER_H
#define EVENTBUILDER_H

#include <string>
#include <iostream>

#include "Tool.h"

#include "TTree.h"

class EventBuilder: public Tool {


 public:

  EventBuilder();
  void Initialise(std::string configfile,DataModel &data);
  void Execute();
  void Finalise(); 


 private:

  float c0,c1,c2,c3,c4,c5;
  int r0,r1,r2,r3,r4,r5;
  int threshnum;
  double threshold;
  TTree* tree;

};


#endif
