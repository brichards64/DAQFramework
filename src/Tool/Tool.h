#ifndef TOOL_H
#define TOOL_H

#include <string>

#include "Store.h"
#include "DataModel.h"

class Tool{

 public:

  virtual void Initialise(std::string configfile,DataModel &data)=0;
  virtual void Execute()=0;
  virtual void Finalise()=0;

 protected:

  Store m_variables;
  DataModel *m_data;

 private:





};

#endif
