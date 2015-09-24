#ifndef MYTOOL_H
#define MYTOOL_H

#include <string>
#include <iostream>

#include "Tool.h"

class MyTool: public Tool {


 public:

  MyTool();
  void Initialise(std::string configfile,Data &data);
  void Execute();
  void Finalise();


 private:





};


#endif
