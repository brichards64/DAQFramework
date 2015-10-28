#ifndef TOOLCHAIN_H
#define TOOLCHAIN_H

#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <pthread.h>

#include "Tool.h"
#include "DataModel.h"

class ToolChain{

 public:

  ToolChain(bool verbose=true, int errorlevel=0); 
  //verbosity: true= print out status messages , false= print only error messages;
  //errorlevels: 0= do not exit; error 1= exit if unhandeled error ; exit 2= exit on handeled and unhandeled errors; 
  
  void Add(std::string name,Tool *tool,std::string configfile="");
  void Initialise();
  void Execute(int repeates=1);
  void Finalise();

  void Interactive();
  static  void *InteractiveThread(void* arg);

  std::string m_command;
  pthread_mutex_t mu_tcommand;
  bool m_newcommand;
  pthread_mutex_t mu_tnewcommand;
  bool m_listen;
  pthread_mutex_t mu_tlisten;
 
private:
  
  bool m_verbose;
  int m_errorlevel;
  std::vector<Tool*> m_tools;
  std::vector<std::string> m_toolnames;
  std::vector<std::string> m_configfiles;
  DataModel m_data;

  pthread_t threads[5];
  
};

#endif
