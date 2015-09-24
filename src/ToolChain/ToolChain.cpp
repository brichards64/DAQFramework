#include "ToolChain.h"

ToolChain::ToolChain(){
 std::cout<<"********************************************************"<<std::endl;
  std::cout<<"**** Tool chain created ****"<<std::endl;
 std::cout<<"********************************************************"<<std::endl<<std::endl;
}


void ToolChain::Add(std::string name,Tool *tool,std::string configfile){

  std::cout<<"Adding Tool=\""<<name<<"\" tool chain"<<std::endl;
  m_tools.push_back(tool);
  m_toolnames.push_back(name);
  m_configfiles.push_back(configfile);
  std::cout<<"Tool=\""<<name<<"\" added successfully"<<std::endl<<std::endl; 

}

void ToolChain::Initialise(){

std::cout<<"********************************************************"<<std::endl;
  std::cout<<"**** Initialising tools in toolchain ****"<<std::endl;
  std::cout<<"********************************************************"<<std::endl<<std::endl;

  for(int i=0 ; i<m_tools.size();i++){  
    
    std::cout<<"Initialising "<<m_toolnames.at(i)<<std::endl;
    m_tools.at(i)->Initialise(m_configfiles.at(i), m_data);
    std::cout<<m_toolnames.at(i)<<" initialised successfully"<<std::endl<<std::endl;
  }

  std::cout<<"**** Tool chain initilised ****"<<std::endl;
    std::cout<<"********************************************************"<<std::endl<<std::endl;
}

void ToolChain::Execute(){
  std::cout<<"********************************************************"<<std::endl;
  std::cout<<"**** Executing tools in toolchain ****"<<std::endl;
  std::cout<<"********************************************************"<<std::endl<<std::endl;

  for(int i=0 ; i<m_tools.size();i++){

    std::cout<<"Executing "<<m_toolnames.at(i)<<std::endl;
    m_tools.at(i)->Execute();
    std::cout<<m_toolnames.at(i)<<" executed  successfully"<<std::endl<<std::endl;
  }

  std::cout<<"**** Tool chain executed ****"<<std::endl;
  std::cout<<"********************************************************"<<std::endl<<std::endl;
}


void ToolChain::Finalise(){
 std::cout<<"********************************************************"<<std::endl;
  std::cout<<"**** Finalising tools in toolchain ****"<<std::endl;
 std::cout<<"********************************************************"<<std::endl<<std::endl;
  for(int i=0 ; i<m_tools.size();i++){

    std::cout<<"Finalising "<<m_toolnames.at(i)<<std::endl;
    m_tools.at(i)->Finalise();
    std::cout<<m_toolnames.at(i)<<" Finalised successfully"<<std::endl<<std::endl;;
  }

  std::cout<<"**** Tool chain Finalised ****"<<std::endl;
std::cout<<"********************************************************"<<std::endl<<std::endl;

}
