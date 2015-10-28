#include "ToolChain.h"

ToolChain::ToolChain(bool verbose,int errorlevel){

  m_verbose=verbose;
  m_errorlevel=errorlevel;
  
  if(m_verbose){  
    std::cout<<"********************************************************"<<std::endl;
    std::cout<<"**** Tool chain created ****"<<std::endl;
    std::cout<<"********************************************************"<<std::endl<<std::endl;
  }
}



void ToolChain::Add(std::string name,Tool *tool,std::string configfile){
  
  if(m_verbose)std::cout<<"Adding Tool=\""<<name<<"\" tool chain"<<std::endl;
  m_tools.push_back(tool);
  m_toolnames.push_back(name);
  m_configfiles.push_back(configfile);
  if(m_verbose)std::cout<<"Tool=\""<<name<<"\" added successfully"<<std::endl<<std::endl; 
  
}



void ToolChain::Initialise(){
  
  if(m_verbose){
    std::cout<<"********************************************************"<<std::endl;
    std::cout<<"**** Initialising tools in toolchain ****"<<std::endl;
    std::cout<<"********************************************************"<<std::endl<<std::endl;
  }
  
  for(int i=0 ; i<m_tools.size();i++){  
    
    if(m_verbose) std::cout<<"Initialising "<<m_toolnames.at(i)<<std::endl;
    
    try{    
      if(m_tools.at(i)->Initialise(m_configfiles.at(i), m_data)){
	if(m_verbose)std::cout<<m_toolnames.at(i)<<" initialised successfully"<<std::endl<<std::endl;
      }
      else{
	std::cout<<"WARNING !!!!! "<<m_toolnames.at(i)<<" Failed to initialise (exit error code)"<<std::endl<<std::endl;
	if(m_errorlevel>1) exit(1);
      }
      
    }
    
    catch(...){
      std::cout<<"WARNING !!!!! "<<m_toolnames.at(i)<<" Failed to initialise (uncaught error)"<<std::endl<<std::endl;
      if(m_errorlevel>0) exit(1);
    }
    
  }
  
  if(m_verbose){std::cout<<"**** Tool chain initilised ****"<<std::endl;
    std::cout<<"********************************************************"<<std::endl<<std::endl;
  }
}



void ToolChain::Execute(int repeates){
  
  for(int i=0;i<repeates;i++){

    if(m_verbose){
      std::cout<<"********************************************************"<<std::endl;
      std::cout<<"**** Executing tools in toolchain ****"<<std::endl;
      std::cout<<"********************************************************"<<std::endl<<std::endl;
    }
    
    for(int i=0 ; i<m_tools.size();i++){
      
      if(m_verbose)    std::cout<<"Executing "<<m_toolnames.at(i)<<std::endl;
      
      try{
	if(m_tools.at(i)->Execute()){
	  if(m_verbose)std::cout<<m_toolnames.at(i)<<" executed  successfully"<<std::endl<<std::endl;
	}
	else{
	std::cout<<"WARNING !!!!!! "<<m_toolnames.at(i)<<" Failed to execute (error code)"<<std::endl<<std::endl;
	if(m_errorlevel>1)exit(1);
	}  
      }
      
      catch(...){
      std::cout<<"WARNING !!!!!! "<<m_toolnames.at(i)<<" Failed to execute (uncaught error)"<<std::endl<<std::endl;
      if(m_errorlevel>0)exit(1);
      }
      
    } 
    if(m_verbose){
      std::cout<<"**** Tool chain executed ****"<<std::endl;
      std::cout<<"********************************************************"<<std::endl<<std::endl;
    }
  }

}



void ToolChain::Finalise(){
  if(m_verbose){
    std::cout<<"********************************************************"<<std::endl;
    std::cout<<"**** Finalising tools in toolchain ****"<<std::endl;
    std::cout<<"********************************************************"<<std::endl<<std::endl;
  }  
  
  for(int i=0 ; i<m_tools.size();i++){
    
    if(m_verbose)std::cout<<"Finalising "<<m_toolnames.at(i)<<std::endl;
    

    try{
      if(m_tools.at(i)->Finalise()){
	if(m_verbose)std::cout<<m_toolnames.at(i)<<" Finalised successfully"<<std::endl<<std::endl;
      }
      else{
	std::cout<<"WRNING !!!!!!! "<<m_toolnames.at(i)<<" Finalised successfully (error code)"<<std::endl<<std::endl;;
	if(m_errorlevel>1)exit(1);
      }  
    }
    
    catch(...){
      std::cout<<"WRNING !!!!!!! "<<m_toolnames.at(i)<<" Finalised successfully (uncaught error)"<<std::endl<<std::endl;;
      if(m_errorlevel>0)exit(1);
    }
    
  }
  
  if(m_verbose){
    std::cout<<"**** Tool chain Finalised ****"<<std::endl;
    std::cout<<"********************************************************"<<std::endl<<std::endl;
  }
}


void ToolChain::Interactive(){
  m_verbose=false;
  m_listen=true;
  m_newcommand=false;
  pthread_mutex_init(&mu_tnewcommand, NULL);
  pthread_mutex_init(&mu_tlisten, NULL);
  pthread_mutex_init(&mu_tcommand, NULL);
  pthread_create(&threads[0], NULL, ToolChain::InteractiveThread, this);
  bool exeloop=false;
  
  while(true){
    pthread_mutex_lock(&mu_tnewcommand); 
    if(m_newcommand){
      pthread_mutex_lock (&mu_tcommand);    
      if(m_command=="Initialise") Initialise();
      else if (m_command=="Execute") Execute();
      else if (m_command=="Finalise") Finalise();
      else if (m_command=="Quit"){	
	pthread_mutex_lock (&mu_tlisten);  
	m_listen=false;
	pthread_mutex_unlock (&mu_tlisten);  
	exit(0);
      }
      else if (m_command=="Start"){
	Initialise();
	exeloop=true;
      }
      else if(m_command=="Pause") exeloop=false;
      else if(m_command=="Unpause") exeloop=true;
      else if(m_command=="Stop") {
	exeloop=false;
	Finalise();
      }
      else std::cout<<"command not recognised please try again"<<std::endl;
      
      m_newcommand=false;
      pthread_mutex_unlock (&mu_tcommand); 
    }
    pthread_mutex_unlock (&mu_tnewcommand); 
    
    if(exeloop) Execute();
  }
  
}

void *ToolChain::InteractiveThread(void* arg){
  ToolChain* self=(ToolChain*)arg;
  
  pthread_mutex_lock (&self->mu_tlisten);  
  while(self->m_listen){
    pthread_mutex_unlock (&self->mu_tlisten);
    pthread_mutex_lock (&self->mu_tnewcommand);
    if(!self->m_newcommand){
    pthread_mutex_unlock (&self->mu_tnewcommand);  
      std::cout<<"Please type command : Start, Pause, Unpause, Stop, Quit (Initialise, Execute, Finalise)"<<std::endl;   
      
      pthread_mutex_lock (&self->mu_tcommand); 
      std::cin>>self->m_command;
      pthread_mutex_unlock (&self->mu_tcommand); 
      
      pthread_mutex_lock (&self->mu_tnewcommand); 
      self->m_newcommand=true;
       
    }
    pthread_mutex_unlock (&self->mu_tnewcommand); 
  }
  pthread_mutex_unlock (&self->mu_tlisten);  
}
