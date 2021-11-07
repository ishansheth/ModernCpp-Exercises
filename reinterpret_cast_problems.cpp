// https://stackoverflow.com/questions/51982709/reinterpret-cast-vs-strict-aliasing
#include <iostream>
#include <cstring>

template <typename T> T transform(T t);

struct my_buffer
{
  char data[128];
  unsigned pos;
  my_buffer() : pos(0) {}

  void rewind(){pos = 0;}

  template <typename T> void push_via_pointer_cast(const T& t)
  {
    *reinterpret_cast<T*>(&data[pos]) = transform(t);
    pos += sizeof(T);
  }

  template <typename T> void pop_via_pointer_cast(T& t)
  {
    t = transform(*reinterpret_cast<T*>(&data[pos]));
    pos += sizeof(T);
  }

  template <typename T> void push_via_mem_copy(const T& t)
  {
    auto temp = transform(t);
    std::memcpy(&data[pos],&temp,sizeof(T));
    pos += sizeof(T);    
  }

  template <typename T> void pop_via_mem_copy(T& t)
  {
    T temp;
    std::memcpy(&temp,&data[pos],sizeof(T));
    t = transform(temp);
    pos += sizeof(T);    
  }

};

template<>
int transform<int>(int x)
{
  return x;
}

template<>
float transform<float>(float x)
{
  return x;
}


template<>
double transform<double>(double x)
{
  return x;
}

int foo( float *f, int *i ) { 
    *i = 1;               
    *f = 0.f;            
   return *i;
}


class Object
{
public:
  int a;
  int b;
  int c;
  std::string str;
  Object():a(0),b(1),c(2),str("ishan")
  {}

  int checkVal(){return a;}
};

int main()
{

  {
    my_buffer b;
    b.push_via_pointer_cast(1);
    b.push_via_pointer_cast(2.0);
    
    b.rewind();
    
    int x;
    double y;
  
    b.pop_via_pointer_cast(x);
    b.pop_via_pointer_cast(y);
    
    std::cout<<x<<"-"<<y<<std::endl;
  }

  {
    my_buffer b;    
    b.push_via_mem_copy(1);
    b.push_via_mem_copy(2.0);
    b.rewind();
    int x;
    double y;
    b.pop_via_mem_copy(x);
    b.pop_via_mem_copy(y);
    std::cout << x <<"-"<< y << '\n';
  }
  
  int a = 0;

  std::cout << a << std::endl; 
  int x = foo(reinterpret_cast<float*>(&a), &a);
  std::cout << a << "\n";

  // interesting reinterpret_cast exercise
  unsigned long testbuf[] = {45,6};

  Object* testPtr = reinterpret_cast<Object*>(testbuf);
  if(testPtr->checkVal())
    {
      std::cout<<"no crash:"<<testPtr->str<<std::endl;
    }
}
