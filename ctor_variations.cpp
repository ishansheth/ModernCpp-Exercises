#include <iostream>
#include <string>
#include <vector>

class Cust
{
  std::string first;
  std::string last;

public:
  
  template<typename T1,typename T2=std::string>
  Cust(T1&& a,T2&& b=""):
    first(std::forward<T1>(a)),last(std::forward<T2>(b))
  {}
  
};

int main()
{
  std::string s = "hello";
  Cust c1{"ishan","sheth"};
  Cust c2{"ishan"};
  Cust c3{s,s};

  using namespace std::literals;
  auto s1 = "42"s;
  std::cout<<"size:"<<s1.size()<<std::endl;

  char z1{'a'};
  char z2{static_cast<char>(z1+1)};
}
