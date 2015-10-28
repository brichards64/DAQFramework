#ifndef ROOTSTOREPSEC_H
#define ROOTSTOREPSEC_H

#include <string>
#include <iostream>
#include <vector>

#include "Tool.h"

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"


class RootStorePSEC: public Tool {


 public:

  RootStorePSEC();
  bool Initialise(std::string configfile,DataModel &data);
  bool Execute();
  bool Finalise();


 private:


 float c0,c1,c2,c3,c4,c5,t;
 int r0,r1,r2,r3,r4,r5;
 TFile *file;
 TTree *tree;

 void WriteElementsTree(std::vector<PSECElement*> *elements);
};


#endif
