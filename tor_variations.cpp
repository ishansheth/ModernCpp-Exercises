#include <iostream>
#include <string>

class Cust
{
  std::string first;
  std::string last;

public:
  
  Cust(const char* a,const char* b):
    first(a),last(b)
  {
    std::cout<<"ctor"<<std::endl;
  }

};


int main()
{
  Cust c1 = "ishan";
}
