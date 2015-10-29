#ifndef STORE_H 
#define STORE_H

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>

class Store{

 public:

  Store();
  void Initialise(std::string filename);
  void Print();
  void Delete();

  template<typename T> void Get(std::string name,T &out){
    std::stringstream stream(m_variables[name]);
    stream>>out;
  }
  
  template<typename T> void Set(std::string name,T in){
    std::stringstream stream;
    stream<<in;
    m_variables[name]=stream.str();
  }
  
 private:

  std::map<std::string,std::string> m_variables;


};

#endif
