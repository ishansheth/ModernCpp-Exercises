#include <string>
#include <iostream>
#include <vector>

auto func3()
{
  static std::string test = "bye";
  auto& result(test);
  return result;
}

decltype(auto) func4()
{
  static std::string test = "bye";
  auto& result(test);
  return result;
}

decltype(auto) func5()
{
  std::string test = "bye";
  return std::move(test);
}

template<typename F,typename...Args>
void forArgs(F&& fn,Args&&...arg)
{
  auto res = std::initializer_list<int>{(fn(std::forward<Args>(arg)))...};
  for(auto& element : res)
    std::cout<<element;
}

template<typename T>
void func6(std::initializer_list<T> arg)
{
  //  std::cout<<arg[0];
}

int main()
{
  auto a = func3();
  static_assert(std::is_same<decltype(a),std::string>(),"");
  std::cout<<a<<std::endl;

  auto& b = func4();
  static_assert(std::is_same<decltype(b),std::string&>(),"");
  std::cout<<b<<std::endl;

  static_assert(std::is_same<decltype(func5()),std::string&&>(), "");
  auto c = func5();
  std::cout<<c<<std::endl;

  forArgs([](const auto& x){return x*2;},1,2,3,4);

  std::vector<int> nums{1,2,3};
  func6({1,2,3,4});
}
