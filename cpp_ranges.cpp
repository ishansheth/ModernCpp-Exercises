#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>
#include <numeric>

std::vector<int> getData()
{
  return std::vector<int>{1,2,3,4,5};
}


int main()
{
  std::vector<int> arr{1,2,3,4,5,6,7,8};
  
  auto results = getData() |  std::views::transform([](int n){return n*2;});
  
  for(const auto& v: results)
    std::cout<<v<<std::endl;
    
  // find minimum element of the vector     
  //auto iter = std::min_element(getData().begin(),getData().end()); will cause seg fault, but using ranges, it will be fine
  
  auto iter = std::min_element(arr.begin(),arr.end());
  std::cout<<"Min element:"<<*iter<<std::endl;
  
  //min element using ranges
  auto minE = std::ranges::min_element(arr);
  std::cout<<"Min element:"<<*minE<<std::endl;
  
  
  // sum of square of values in vec
  
  auto view = std::views::transform(arr,[](int i ){return i*i;});
  auto sum_sq = std::accumulate(view.begin(),view.end(),0);
  std::cout<<sum_sq<<std::endl;
  
}
