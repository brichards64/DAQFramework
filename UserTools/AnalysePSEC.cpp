#include "AnalysePSEC.h"

AnalysePSEC::AnalysePSEC():Tool(){}


bool AnalysePSEC::Initialise(std::string configfile, DataModel &data){

  m_variables.Initialise(configfile);

  m_variables.Get("threshold",threshold);
  
  m_data= &data;

  cosmics =new TTree("Cosmics","Cosmics");
  m_data->AddTTree("Cosmics",cosmics);
  
  cosmics->Branch("in",&in,"in/F");
  cosmics->Branch("out",&out,"out/F");


  
  events=m_data->GetTTree("Events");

  return true;
  
  
}


bool AnalysePSEC::Execute(){
  
  events->SetBranchAddress("c0", &c0, &b_c0);
  events->SetBranchAddress("c1", &c1, &b_c1);
  events->SetBranchAddress("c2", &c2, &b_c2);
  events->SetBranchAddress("c3", &c3, &b_c3);
  events->SetBranchAddress("c4", &c4, &b_c4);
  events->SetBranchAddress("c5", &c5, &b_c5);

  events->SetBranchAddress("r0", &r0, &b_r0);
  events->SetBranchAddress("r1", &r1, &b_r1);
  events->SetBranchAddress("r2", &r2, &b_r2);
  events->SetBranchAddress("r3", &r3, &b_r3);
  events->SetBranchAddress("r4", &r4, &b_r4);
  events->SetBranchAddress("r5", &r5, &b_r5);

  Long64_t nentries = events->GetEntriesFast();
  
  for (int i=0;i<nentries;i++){
    events->GetEntry(i);
    if (c0>threshold && c1>threshold){
      in=c0;
      out=c1;
      cosmics->Fill();
    }
    else if(c2>threshold && c3>threshold){
      in=c2;
      out=c3;
      cosmics->Fill();
    }
    else if(c4>threshold && c5>threshold){
      in=c4;
      out=c5;
      cosmics->Fill();
    }
  }

  return true;
}


bool AnalysePSEC::Finalise(){

  return true;
}
