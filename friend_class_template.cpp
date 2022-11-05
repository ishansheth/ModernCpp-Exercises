#include <iostream>

template<typename T> class A;

template<typename T>
class B
{
  friend class A<B>;
  friend class A<int>;

  T x;
  public:  

  B(const T& a) : x(a)
  {}
  ~B() = default;

  template<typename U>  
  void test()
  {

  }

};

template<typename T>
class A
{
  T x;

  public:  
  A(const T& a) : x(a)
  {}

  ~A() = default;

  template<typename U>  
  void test(B<U> x)
  {
    std::cout<<x.x<<std::endl;
  }

};




int main()
{

std::cout << std::boolalpha << std::is_same<std::map<json::string_t, json>, json::object_t>::value << std::endl;

  B<int> bobj(3);
  A<B<int>> aobj(bobj);
  // this will compile because of the line
  // friend class A<B>;
  // since A<B> is a friend of B, it can access private members of B instantiated with any type 
  aobj.test(bobj);

  A<int> aobj2(2);
  // this will compile because of the line
  // friend class A<int>;
  // since A<int> is a friend of B, it can access private members of B instantiated with any type 
  aobj2.test(bobj);

  // A instantiated with any other type can not access private members of B. Below piece of code
  // will fail to compile 
  /*
    A<float> aobj3(2.4);
    aobj3.test(bobj);
  
  */

}