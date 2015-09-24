#include "ToolChain.h"
#include "PSEC4Reader.h"
#include "PSEC4Sim.h"
//#include "EventBuilder.h"
//#include "AnalysePSEC.h"
#include "RootStorePSEC.h"


int main(){

  ToolChain tools;
  PSEC4Reader rpsec;
  //PSEC4Sim spsec;
  //  EventBuilder eventbuilder;
  //AnalysePSEC apsec;
  RootStorePSEC rootpsec;


  tools.Add("PSEC4Reader",&rpsec,"configfiles/PSEC4config");
  for(int j=0;j<72;j++){
    for(int i=0;i<8;i++){
      PSEC4Sim *spsec=new  PSEC4Sim;
      tools.Add("PSEC4Sim",spsec,"configfiles/PSEC4config");
    }
  }
  //tools.Add("PSEC4Sim",&spsec,"configfiles/PSEC4config");
  // tools.Add("EventBuilder",&eventbuilder,"EventBuilderconfig");
  //tools.Add("PSEC4Analyser",&apsec,"EventBuilderconfig");
  tools.Add("PSEC4RootStore",&rootpsec,"configfiles/PSEC4config");
  
  tools.Initialise();
  tools.Execute();
  tools.Finalise();


  return 0;

}
