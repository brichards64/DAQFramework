#include "PSEC4Sim.h"

PSEC4Sim::PSEC4Sim():Tool(){}


void PSEC4Sim::Initialise(std::string configfile, DataModel &data){

  m_variables.Initialise(configfile);
  // m_variables.Print();
  m_data= &data;

 

 m_variables.Get("num_readouts",num_readouts);
 m_variables.Get("trig_mode",trig_mode);
 m_variables.Get("acq_rate_hertz",acq_rate_hertz );


 acq_rate_usecs = (int) (1000000 / acq_rate_hertz); 

  


}


void PSEC4Sim::Execute(){
  
  PSECElement *tmp=new PSECElement(6);
  
  tmp->starttime=0;
  tmp->timestep=acq_rate_usecs;
  tmp->numpoints=256;
  tmp->numreadouts=num_readouts;

  m_data->vars.Get("crateid",tmp->crateid);
  m_data->vars.Get("cardid",tmp->cardid);
  tmp->cardid++;
  if(tmp->cardid>7){
    tmp->crateid++;
    tmp->cardid=0;
    m_data->vars.Set("crateid",tmp->crateid);
  }
  m_data->vars.Set("cardid",tmp->cardid);
  std::cout<<"cardid "<<tmp->cardid<<" crateid "<<tmp->crateid<<std::endl;
  int tmppmtid;
  m_data->vars.Get("pmtid",tmppmtid);
  tmppmtid+=1;
  m_data->vars.Set("pmtid",tmppmtid+5);

  double pi=3.14159265351;
  double angle =(2*pi)/(6*8);
  double r=5.5;
  double dist=22.0/72.0;
  

  for (int i=0;i<6;i++){
    tmp->pmtids[i]=i+tmppmtid;
    std::vector<float> tmploc;
    tmploc.push_back(cos((((tmp->cardid)*6)+(i+1))*angle)*r);
    std::cout<<"i= "<<i<<" angle multiplier "<<((tmp->cardid)*6)+(i+1)<<std::endl;

    tmploc.push_back(sin((((tmp->cardid)*6)+(i+1))*angle)*r);
    tmploc.push_back((dist/2.0)+(tmp->crateid*dist));
    tmp->pmtlocations.push_back(tmploc);
  }
  
  
  TRandom *eventGenerator = new TRandom();
  
time_t seconds;

  seconds = time (NULL);
  eventGenerator->SetSeed((uint) seconds);
  std::vector<std::vector<std::vector<float> > >tmpf3;
  std::vector< std::vector<std::vector<int> > >tmpi3;


  for(int k=0;k<num_readouts;k++){

  std::vector<std::vector<float> >tmpf2;
  std::vector<std::vector<int> >tmpi2;
  
  for(int j=0;j<6;j++){
    std::vector<float> tmpf;
    std::vector<int> tmpi;
    
    for (int i=0;i<256;i++){
      tmpf.push_back(eventGenerator->Gaus(0.0055,0.002));
      tmpi.push_back(floor(eventGenerator->Gaus(2100.0,200.0)));
    }
    tmpf2.push_back(tmpf);
    tmpi2.push_back(tmpi);
  }

  tmpf3.push_back(tmpf2);
  tmpi3.push_back(tmpi2);
  }
  
  tmp->caldata=tmpf3;
  tmp->rawdata=tmpi3;
  
  m_data->elements.push_back(tmp);
}


void PSEC4Sim::Finalise(){


}

