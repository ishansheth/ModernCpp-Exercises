#include <iostream>
#include "type_erasure.hpp"

int main()
{
  Shelf ss;
  ss.for_each_book([](auto&& book){std::cout<<"->"<<book<<std::endl;});
}
