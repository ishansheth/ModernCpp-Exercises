/*

type function is a function that either takes one type 
argument or produces at lease one type as a result

  e.g. is_poymorphic<T>::value

 */

#include <type_traits>
#include <iostream>
#include <string>
#include <array>

struct A
{
  int m;
};

struct B
{
  virtual void foo();
};

constexpr int on_stack_max = sizeof(int);

template<typename T,std::size_t N>
struct On_heap
{
  On_heap(): p(new T[N]){std::cout<<"allocating on heap"<<std::endl;}
  ~On_heap(){delete p;}

  // input as an index, return the reference of the element at that index
  T& operator*(std::size_t index)
  {
    return *(p+index);
  }

  // input as an index, return the element at that index
  T* operator->()
  {
    return p;
  }

  T& operator[](std::size_t index)
  {
    return *(p+index);
  }

  On_heap(const On_heap&) = delete;
  On_heap& operator=(const On_heap&) = delete;

private:
  T* p;
};

template<typename T,std::size_t N>
struct Scoped
{
  Scoped(){std::cout<<"allocating on stack"<<std::endl;}

  T& operator[](std::size_t index)
  {
    return p[index];
  }

  Scoped(const Scoped&) = delete;
  Scoped& operator=(const Scoped&) = delete;

private:
  T p[N];
};

template<typename T,std::size_t N>
struct Obj_holder
{
  using type = typename std::conditional<(sizeof(T)<=on_stack_max),Scoped<T,N>,On_heap<T,N>>::type;
};


// type alias
template<bool C,typename T, typename F>
using Conditional = typename std::conditional<C,T,F>::type;

// selecting a function

struct X
{
  void operator()(int x){std::cout<<"X:"<<x<<std::endl;}
};

struct Y
{
  void operator()(int x){std::cout<<"Y:"<<x<<std::endl;}
};



void f()
{
  typename Obj_holder<char,20>::type v1;    // v1 type is Scoped<double>, on stack
  typename Obj_holder<double,20>::type v2;   //v2 type is On_heap<std::array>, on heap

  for(unsigned int i = 0; i < 10; i++)
  {
     v1[i] = i;
     v2[i] = i+1;   
  }

  for(unsigned int i = 0; i < 10; i++)
  {
    std::cout<<"stack:"<<int(v1[i])<<std::endl; // since its an array of char, count can't print without casting
    std::cout<<"heap:"<<v2[i]<<std::endl;
  }

}

int main()
{
  std::cout<<std::is_polymorphic<A>::value<<std::endl;
  std::cout<<std::is_polymorphic<B>::value<<std::endl;

  Conditional<(sizeof(int)>4),X,Y>{}(7);   // create an object of X or Y and call it
  f();
}

