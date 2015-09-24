#include "PSEC4Reader.h"

PSEC4Reader::PSEC4Reader():Tool(){}


void PSEC4Reader::Initialise(std::string configfile, DataModel &data){
 
  m_variables.Initialise(configfile);
  
  // m_variables.Print();
  m_data= &data;
  
  if(command.INITIALIZE() != 0){
    return;
    
  }
  
  m_variables.Get("num_readouts",num_readouts);
  m_variables.Get("trig_mode",trig_mode);
  m_variables.Get("acq_rate_hertz",acq_rate_hertz );
  
  acq_rate_usecs = (int) (1000000 / acq_rate_hertz); 
  
  m_data->vars.Set("crateid",0);
  m_data->vars.Set("cardid",0);
  m_data->vars.Set("pmtid",5);
  
}


void PSEC4Reader::Execute(){
  
  PSECElement *tmp=new PSECElement(6);
  tmp->crateid=0;
  tmp->cardid=0;
  tmp->starttime=0;
  tmp->timestep=acq_rate_usecs;
  tmp->numpoints=256;
  tmp->numreadouts=num_readouts;
  double pi=3.14159265351;
  double angle =(2*pi)/(6*8);
  double r=5.5;
  double dist=22/72;
  for (int i=0;i<6;i++){
    tmp->pmtids[i]=i;
    std::vector<float> tmploc;
    tmploc.push_back(cos((i+1)*angle)*r);
    tmploc.push_back(sin((i+1)*angle)*r);
    tmploc.push_back(dist/2);
    tmp->pmtlocations.push_back(tmploc);
  }
  
  tmp->caldata=command.GETDATA(num_readouts, trig_mode, acq_rate_usecs);
  tmp->rawdata=command.rawdat;
  
  m_data->elements.push_back(tmp);
}


void PSEC4Reader::Finalise(){


}
