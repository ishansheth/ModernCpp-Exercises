/*
From the C++ Programming language by Bjarne Stroustrup page 764
*/
#include <iostream>

class shape
{
public:
  virtual void draw() = 0;
};


class triangle : public shape
{
public:
  //  triangle(int x):a(x){}
  
  void draw() override
  {
    std::cout<<"drawing triangle"<<std::endl;
  }
};

class circle : public shape
{
  int r;
public:
    circle():r(0){}
  //  circle(int x):r(x){}
  
  void draw() override
  {
    std::cout<<"drawing circle"<<std::endl;
  }
};

// template conversion
template<typename T>
class Ptr
{
  T* p;
public:
  Ptr(T* a):p(a){}

  template<typename T2>
  operator Ptr<T2>()
  {
    return Ptr<T2>{p};
  }
};

/*

main view: | image[0] | image[1] | image[2] |
maul view: |p[0]|p[1] |p[2]|p[3] |p[4]|p[5] |

when p[1] is used to invoke a function, then there is no
virtual function pointer at that location, so it fails
*/

void maul(shape* p,int n)
{
  for(int i = 0;i<n;i++)
    p[i].draw();    // dangerous code!! seg fault if sizeof(Circle) > sizeof(Shape) otherwise its ok
}

int main()
{
  circle image[10];
  maul(image,10);

  Ptr<circle> pc{&image[0]};
  Ptr<shape> ps{pc};
  //Ptr<circle> pc2{ps};
  
  return 0;
}


