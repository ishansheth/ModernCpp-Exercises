#include <iostream>
#include <unordered_map>
#include <array>

bool sumOfTwoArray(int* arr1, int* sz1, int* arr2, int sz2)  
{


  
}

int main()
{
  std::array<std::pair<int,std::string>,8>  color_val;

  color_val[0] = {1,"blue"};
  color_val[1] = {1,"red"};
  color_val[2] = {2,"violet"};
  color_val[3] = {3,"green"};
  color_val[4] = {4,"yellow"};
  color_val[5] = {5,"red"};
  color_val[6] = {5,"red"};


  for(auto& element: color_val)
    {
      std::cout<<element.first<<element.second<<std::endl;
    }
}
