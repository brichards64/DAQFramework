#include "EventBuilder.h"

EventBuilder::EventBuilder():Tool(){}


void EventBuilder::Initialise(std::string configfile, DataModel &data){

  m_variables.Initialise(configfile);
  m_data= &data;
  
  m_variables.Get("threshnum",threshnum);
  m_variables.Get("threshold",threshold);


  tree =new TTree("Events","Events");
  m_data->AddTTree("Events",tree);

  tree->Branch("c0",&c0,"c0/F");
  tree->Branch("c1",&c1,"c1/F");
  tree->Branch("c2",&c2,"c2/F");
  tree->Branch("c3",&c3,"c3/F");
  tree->Branch("c4",&c4,"c4/F");
  tree->Branch("c5",&c5,"c5/F");
  
  
  tree->Branch("r0",&r0,"r0/I");
  tree->Branch("r1",&r1,"r1/I");
  tree->Branch("r2",&r2,"r2/I");
  tree->Branch("r3",&r3,"r3/I");
  tree->Branch("r4",&r4,"r4/I");
  tree->Branch("r5",&r5,"r5/I");
  

}


void EventBuilder::Execute(){

  for (int g=0;g<m_data->elements.size();g++){
  for (int i=0;i<m_data->elements.at(g)->caldata.size();i++){
    for (int j=0 ; j<m_data->elements.at(g)->caldata.at(i).at(0).size();j++){
      int overthresh=0;
      for (int k=0;k<6;k++){
	if (m_data->elements.at(g)->caldata.at(i).at(k).at(j)>threshold) overthresh++;
      }
      if (overthresh >threshnum){
	c0=m_data->elements.at(g)->caldata.at(i).at(0).at(j);
	c1=m_data->elements.at(g)->caldata.at(i).at(1).at(j);
	c2=m_data->elements.at(g)->caldata.at(i).at(2).at(j);
	c3=m_data->elements.at(g)->caldata.at(i).at(3).at(j);
	c4=m_data->elements.at(g)->caldata.at(i).at(4).at(j);
	c5=m_data->elements.at(g)->caldata.at(i).at(5).at(j);
	
	r0=m_data->elements.at(g)->rawdata.at(i).at(0).at(j);
	r1=m_data->elements.at(g)->rawdata.at(i).at(1).at(j);
	r2=m_data->elements.at(g)->rawdata.at(i).at(2).at(j);
	r3=m_data->elements.at(g)->rawdata.at(i).at(3).at(j);
	r4=m_data->elements.at(g)->rawdata.at(i).at(4).at(j);
	r5=m_data->elements.at(g)->rawdata.at(i).at(5).at(j);
	
	tree->Fill();

      }
	
    }
  }
  
}
}

void EventBuilder::Finalise(){


}
