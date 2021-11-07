#include <iostream>
#include <limits>

// this is to check if we can negate the minimum integer value
int main()
{
  auto i = std::numeric_limits<int>::max();
  std::cout<<i<<std::endl;

  i = -i;
  std::cout<<i<<std::endl;

  char c = '0';
  std::cout<<int(c)<<std::endl;
}
