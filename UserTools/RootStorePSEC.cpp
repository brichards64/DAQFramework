#include "RootStorePSEC.h"

RootStorePSEC::RootStorePSEC():Tool(){}


bool RootStorePSEC::Initialise(std::string configfile, DataModel &data){

  // m_variables.Initialise(configfile);

  m_data= &data;

 file=new TFile("output.root","RECREATE");
 /**tree=new TTree("Data","Data");
  
  tree->Branch("c0",&c0,"c0/F");
  tree->Branch("c1",&c1,"c1/F");
  tree->Branch("c2",&c2,"c2/F");
  tree->Branch("c3",&c3,"c3/F");
  tree->Branch("c4",&c4,"c4/F");
  tree->Branch("c5",&c5,"c5/F");
  tree->Branch("t",&t,"t/F");

 
  tree->Branch("r0",&r0,"r0/I");
  tree->Branch("r1",&r1,"r1/I");
  tree->Branch("r2",&r2,"r2/I");
  tree->Branch("r3",&r3,"r3/I");
  tree->Branch("r4",&r4,"r4/I");
  tree->Branch("r5",&r5,"r5/I");
  */

 return true;
}


bool RootStorePSEC::Execute(){
  
  tree=new TTree("Elements","Elements");
 
  float pmtX,pmtY,pmtZ,theta;
  int points,pmtid,crateid,cardid;
  //float *time,*calib;
  PSECElement *element;
  
  tree->Branch("crateid",&crateid,"crateid/I");
  tree->Branch("cardid",&cardid,"cardid/I");
  tree->Branch("pmtid",&pmtid,"pmtid/I");
  tree->Branch("pmtX",&pmtX,"pmtX/F");
  tree->Branch("pmtY",&pmtY,"pmtY/F");
  tree->Branch("pmtZ",&pmtZ,"pmtZ/F");
  tree->Branch("theta",&theta,"theta/F");
  tree->Branch("points",&points,"points/I");
  
  points=m_data->elements.at(0)->numpoints*m_data->elements.at(0)->numreadouts;
  float time[points],calib[points];
  int raw[points];
  tree->Branch("time",time,"time[points]/F"); 
  tree->Branch("raw",raw,"raw[points]/I"); 
  tree->Branch("clib",calib,"calib[points]/F");
  
  for (int g=0;g<m_data->elements.size();g++){
   element=m_data->elements.at(g);
   points=element->numpoints*element->numreadouts;
   crateid=element->crateid;
   cardid=element->cardid; 
   

  for(int chan=0;chan<element->channels;chan++){
 
     pmtid=element->pmtids[chan];
     pmtX=element->pmtlocations.at(chan).at(0);
     pmtY=element->pmtlocations.at(chan).at(1);
     pmtZ=element->pmtlocations.at(chan).at(2);
     theta=element->pmtlocations.at(chan).at(3);
     //raw=new int[points];
     //time=new float[points];
     //calib= new float[points];
     
     for(int i=0;i<element->numreadouts;i++){
       for(int j=0;j<element->numpoints;j++){
	 // std::cout<<element->caldata.at(i).at(chan).at(j)<<std::endl;
	 time[(i*element->numpoints)+j]=element->starttime+(element->timestep*((i*element->numpoints)+j));
	 raw[(i*element->numpoints)+j]=element->rawdata.at(i).at(chan).at(j);
	 calib[(i*element->numpoints)+j]=element->caldata.at(i).at(chan).at(j);
	 

       }
     }
     
     tree->Fill();
  }
  }  
  
  file->Add(m_data->GetTTree("Events"));
  file->Add(m_data->GetTTree("Cosmics"));
  
  return true;
}
   
bool RootStorePSEC::Finalise(){
  
  file->Write();
       //std::cout<<"DEBUG 9 "<<std::endl;
  file->Close();

  return true;
}


void RootStorePSEC::WriteElementsTree(std::vector<PSECElement*> *elements){

 tree=new TTree("Elements","Elements");

 for (int i=0;i<elements->size();i++){
  

   tree->Branch("c0",&c0,"c0/F");


 }

  tree->Branch("c1",&c1,"c1/F");
  tree->Branch("c2",&c2,"c2/F");
  tree->Branch("c3",&c3,"c3/F");
  tree->Branch("c4",&c4,"c4/F");
  tree->Branch("c5",&c5,"c5/F");
  tree->Branch("t",&t,"t/F");

 
  tree->Branch("r0",&r0,"r0/I");
  tree->Branch("r1",&r1,"r1/I");
  tree->Branch("r2",&r2,"r2/I");
  tree->Branch("r3",&r3,"r3/I");
  tree->Branch("r4",&r4,"r4/I");
  tree->Branch("r5",&r5,"r5/I");



}
