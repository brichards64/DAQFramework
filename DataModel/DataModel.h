#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <map>
#include <string>
#include <vector>

#include "TTree.h"
#include "TBranch.h"

#include "Store.h"

struct PSECElement{
  
  
  int channels;
  int crateid;
  int cardid;
  int pmtids[6];
  int starttime;
  float timestep;
  int numpoints;
  int numreadouts;
  std::vector<std::vector<float> > pmtlocations;
  
  std::vector<std::vector<std::vector< float > > > caldata;
  std::vector<std::vector<std::vector< int > > > rawdata;
  
  PSECElement(int chanin){channels=chanin;};
  
  
};

class DataModel{


 public:
  
  DataModel();
  TTree* GetTTree(std::string name);
  void AddTTree(std::string name,TTree *tree);

  Store vars;

  std::vector<PSECElement*> elements;


 private:
  
  std::map<std::string,TTree*> m_trees; 
  
  
  
};




#endif
