#include "ToolChain.h"
//#include "PSEC4Reader.h"
//#include "PSEC4Sim.h"
//#include "EventBuilder.h"
//#include "AnalysePSEC.h"
//#include "RootStorePSEC.h"
#include "test.h"

int main(){

  ToolChain tools(true,0);
  //PSEC4Reader rpsec;
  //PSEC4Sim spsec;
  //EventBuilder eventbuilder;
  //AnalysePSEC apsec;
  //RootStorePSEC rootpsec;
  test bob;  

  tools.Add("test",&bob);
  //int boards=(72*8)-1;
  
  //tools.Add("PSEC4Reader",&rpsec,"configfiles/PSEC4config");
  /*for(int j=0;j<boards;j++){
    PSEC4Sim *spsec=new  PSEC4Sim;
    tools.Add("PSEC4Sim",spsec,"configfiles/PSEC4config");
    }*/
  //tools.Add("PSEC4Sim",&spsec,"configfiles/PSEC4config");
  //tools.Add("EventBuilder",&eventbuilder,"configfiles/EventBuilderconfig");
  //tools.Add("PSEC4Analyser",&apsec,"EventBuilderconfig");
  //tools.Add("PSEC4RootStore",&rootpsec,"configfiles/PSEC4config");
  
  tools.Interactive();
  //  tools.Initialise();
  //tools.Execute();
  //tools.Finalise();
  
  
  return 0;
  
}
