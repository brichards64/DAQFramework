#include "EventBuilder.h"

EventBuilder::EventBuilder():Tool(){}


void EventBuilder::Initialise(std::string configfile, DataModel &data){

  m_variables.Initialise(configfile);
  m_data= &data;
  
  m_variables.Get("threshnum",threshnum);
  m_variables.Get("threshold",threshold);
 
  tree =new TTree("Events","Events");
  m_data->AddTTree("Events",tree);

  tree->Branch("evt",&evt,"evt/I");
  tree->Branch("nhits",&nhits,"nhits/I");
  tree->Branch("hitx",&hitx,"hitx[nhits]/f");
  tree->Branch("hity",&hity,"hity[nhits]/f");
  tree->Branch("hitz",&hitz,"hitz[nhits]/f");
  tree->Branch("hittheta",&hittheta,"hittheta[nhits]/f");
  tree->Branch("hitt",&hitt,"hitt[nhits]/f");
  tree->Branch("hite",&hite,"hite[nhits]/f");

  /*
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
  */

}


void EventBuilder::Execute(){
      //std::cout<<"Debug 1"<<std::endl;
  
  // float threashold=0.003;
  int totaltime=m_data->elements.at(0)->numpoints * m_data->elements.at(0)->numreadouts;
  //std::cout<<"totaltime="<<totaltime<<std::endl;
  int overthreshnum[totaltime];
  std::vector<std::vector<int > > overthreshpmt; 
     //std::cout<<"Debug 2"<<std::endl;
  for (int time=0;time<totaltime;time++){
    //std::cout<<"time="<<time<<std::endl;
     //std::cout<<"Debug 3"<<std::endl;
     overthreshnum[time]=0;
     std::vector<int>tmp;
    for (int pmt=0;pmt<(m_data->elements.size())*6;pmt++){
           //std::cout<<"Debug 4"<<std::endl;
	   int element=floor(pmt/m_data->elements.at(0)->channels);
	   int channel;
	   if(pmt<m_data->elements.at(0)->channels){
	     channel=pmt;
	   }
	   
	   else{ 
	     channel=pmt - (m_data->elements.at(0)->channels*(element));
	   }
	   
	   int readout=floor(time/m_data->elements.at(0)->numpoints);
	   int point;
	   if(readout<1){
	     point= time;
	   }
	   else{
	     point= time -((readout)*m_data->elements.at(0)->numpoints);
	   }
	  
	   //std::cout<<"time="<<time<<std::endl;
	   //std::cout<<"pmt="<<pmt<<std::endl;
	   //std::cout<<"element="<<element<<std::endl;
	   //std::cout<<"channel="<<channel<<std::endl;
	   //std::cout<<"readout="<<readout<<std::endl;
	   //std::cout<<"point="<<point<<std::endl;
	   
	   //std::cout<<"Debug 4a"<<std::endl;
	   //std::cout<<"val "<<threshold<<std::endl;
	    // std::cout<<"val "<<(m_data->elements.at(element)->caldata.at(readout).at(channel).at(point))<<std::endl;
	   if(m_data->elements.at(element)->caldata.at(readout).at(channel).at(point)>threshold){
	     //std::cout<<"Debug 4b"<<std::endl;
	     overthreshnum[time]++;
	     tmp.push_back(pmt);
	   }
	   //std::cout<<"Debug 4c"<<std::endl;
	   //overthreshpmt.push_back(tmp);
	   //std::cout<<"Debug 4d"<<std::endl;
    }

    overthreshpmt.push_back(tmp);
    //std::cout<<"Debug 4e"<<std::endl;
  }
  
  /*
  std::cout<<"totaltime="<<totaltime<<std::endl;
  std::cout<<"vec total="<<overthreshpmt.size()<<std::endl;
  
  for(int i=0;i<totaltime;i++){
    std::cout<<"i="<<i<<std::endl;
    std::cout<<"overthreshnum="<<overthreshnum[i]<<std::endl;
    std::cout<<"vecvalue="<<overthreshpmt.at(i).size()<<std::endl;
    std::cout<<"equal="<<(overthreshnum[i]==overthreshpmt.at(i).size())<<std::endl;
  }
  */
  evt=0;
  ///////////////////////////////
  //filling events
  //////////////////////////////
  
  //std::cout<<"Debug 5"<<std::endl;
  for (int time=0;time<totaltime;time++){
    //std::cout<<"Debug 6"<<std::endl;
    
    nhits=0;
    //std::cout<<"over thresh = "<<overthreshpmt.at(time).size()<<std::endl;
    if (overthreshpmt.at(time).size()>threshnum){
      //std::cout<<"In baby"<<std::endl;
      evt++;
      int hit=-1;
      for (int i=-5;i<6;i++){
	
	if(time+i<0)continue;
	if(time+i>=totaltime)continue;
	 //std::cout<<"bdebug 1"<<std::endl;
	nhits+=overthreshpmt.at(time+i).size();
		 //std::cout<<"bdebug 2"<<std::endl;
      }
      
      //std::cout<<"nhits="<<nhits<<std::endl;

	 //std::cout<<"bdebug 3"<<std::endl;
      for (int i=-5;i<6;i++){
	//std::cout<<"bdebug 4"<<std::endl;
	 //std::cout<<"i= "<<i<<std::endl;
	 //std::cout<<"time="<<time<<std::endl;
	 //std::cout<<"time+i="<<time+i<<std::endl;
	if(time+i<0)continue;
	if(time+i>=totaltime)continue;

	//std::cout<<"vecsize="<<overthreshpmt.at(time+i).size()<<std::endl;

  for(int tmphit=0;tmphit<overthreshpmt.at(time+i).size();tmphit++){
    hit++;
	  //std::cout<<"bdebug 5"<<std::endl;
	  //std::cout<<"time="<<time<<std::endl;
	  //std::cout<<"i="<<i<<std::endl;
	  //std::cout<<"time+i="<<time+i<<std::endl;
	  //std::cout<<"hit="<<hit<<std::endl;
	  //std::cout<<"overthresh size ="<<overthreshpmt.size()<<std::endl;
	  //	  std::cout<<"overthresh size2 ="<<overthreshpmt.at(time+i).size()<<std::endl;
	  //std::cout<<"overthreshpmt.at(time+i).at(hit)="<<overthreshpmt.at(time+i).at(hit)<<std::endl;
	  int pmt=overthreshpmt.at(time+i).at(tmphit);
	  //std::cout<<"bdebug 6"<<std::endl;
	  
	  int element=floor(pmt/m_data->elements.at(0)->channels);
	  int channel;
	  if(pmt<m_data->elements.at(0)->channels){
	    channel=pmt;
	  }
	  else{ 
	    channel=pmt - (m_data->elements.at(0)->channels*(element));
	  }
	  	  	 //std::cout<<"bdebug 8"<<std::endl;
	  int readout=floor((time+i)/m_data->elements.at(0)->numpoints);
	  int point;
	  if(readout<1){
	     point= (time+i);
	  }
	  else{
	    point= (time+i) -((readout)*m_data->elements.at(0)->numpoints);
	  }
	  
	  // std::cout<<"time="<<time<<std::endl;
	  //std::cout<<"pmt="<<pmt<<std::endl;
	  //std::cout<<"element="<<element<<std::endl;
	  //std::cout<<"channel="<<channel<<std::endl;
	  //std::cout<<"readout="<<readout<<std::endl;
	  //std::cout<<"point="<<point<<std::endl;
	 

	  
	  hitx[hit]=m_data->elements.at(element)->pmtlocations.at(channel).at(0);
	  hity[hit]=m_data->elements.at(element)->pmtlocations.at(channel).at(1);
	  hitz[hit]=m_data->elements.at(element)->pmtlocations.at(channel).at(2);
	  hittheta[hit]=m_data->elements.at(element)->pmtlocations.at(channel).at(3);
	  hitt[hit]=(time+i);
	  hite[hit]=m_data->elements.at(element)->caldata.at(readout).at(channel).at(point);
	  //if(hite[hit]<0.002){
	  std::cout<<"1hite[hit]="<<hite[hit]<<" "<<hit<<std::endl;
	    // }
	}
       
	//std::cout<<"c debug 1"<<std::endl;
      }
      
      //   for (int i=0;i<nhits;i++){
	//std::cout<<"hit[e]="<<hite[i]<<std::endl;
      //}

      tree->Fill();
      //std::cout<<"filled"<<std::endl;
      //tree->Fill();
      time=time+5;
    }
   
  }
  
  /*
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
  */

}

void EventBuilder::Finalise(){
  
  
}
