#include "Store.h"
#include <iostream>
#include <string>


int main(){

  Store data;

  data.Initialise("test");
  data.Print();
  
  int a;
  double b;
  float c;
  std::string d;

  data.Get("A",a);
  data.Get("B",b);
  data.Get("C",c);
  data.Get("D",d);

  std::cout<<"A= "<<a<<std::endl;
  std::cout<<"B= "<<b<<std::endl;
  std::cout<<"C= "<<c<<std::endl;
  std::cout<<"D= "<<d<<std::endl;

  int tt=22;
  double rr=45.36;
  data.Set("tt",tt);
  data.Set("rr",rr);

  data.Print();


  return 0;
}
