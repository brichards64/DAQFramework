#ifndef EVENTBUILDER_H
#define EVENTBUILDER_H

#include <string>
#include <iostream>

#include "Tool.h"

#include "TTree.h"

class EventBuilder: public Tool {


 public:

  EventBuilder();
  bool Initialise(std::string configfile,DataModel &data);
  bool Execute();
  bool Finalise(); 


 private:

  //  float c0,c1,c2,c3,c4,c5;
  //int r0,r1,r2,r3,r4,r5;
  int threshnum;
  double threshold;
  TTree* tree;

  int evt;
  int nhits;
  float hitx[20000];
  float hity[20000];
  float hitz[20000];
  float hittheta[20000];
  float hitt[20000];
  float hite[20000];


};


#endif
