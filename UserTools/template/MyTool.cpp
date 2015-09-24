#include "MyTool.h"

MyTool::MyTool():Tool(){}


void MyTool::Initialise(std::string configfile, Data &data){

  m_variables.Initialise(configfile);
  m_variables.Print();

  m_data= &data;


}


void MyTool::Execute(){


}


void MyTool::Finalise(){


}
