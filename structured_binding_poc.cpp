#include <iostream>
#include <tuple>

std::tuple<int,char,double> getTuple()
{
  int a = 10;
  char b = 'b';
  double c = 10.5;

  return std::make_tuple(a,b,c);
}

void iterateForLoop()
{
  for(auto[i,ch] = std::pair(0U,'a'); i<42; i++)
    {
      std::cout<<"i:"<<i<<"->"<<ch<<std::endl;
      ch++;
    }
}



int main()
{
  auto [x,y,z] = getTuple();
  std::cout<<x<<":"<<y<<":"<<z<<std::endl;
  iterateForLoop();
}
