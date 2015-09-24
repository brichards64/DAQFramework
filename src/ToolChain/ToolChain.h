#ifndef TOOLCHAIN_H
#define TOOLCHAIN_H

#include <vector>
#include <string>
#include <iostream>
#include <vector>

#include "Tool.h"
#include "DataModel.h"

class ToolChain{

 public:

  ToolChain();
  void Add(std::string name,Tool *tool,std::string configfile);
  void Initialise();
  void Execute();
  void Finalise();

 private:

  std::vector<Tool*> m_tools;
  std::vector<std::string> m_toolnames;
  std::vector<std::string> m_configfiles;
  DataModel m_data;

};

#endif
