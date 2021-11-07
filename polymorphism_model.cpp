#include <iostream>

class interface
{
public:
  virtual void add() = 0;
  virtual void sub() = 0;
};


class A : public interface
{
public:
  virtual void add() override
  {
    std::cout<<"A::in add"<<std::endl;
  }

  virtual void sub() override
  {
    std::cout<<"A::in sub"<<std::endl;
  }

};

class B : public interface
{
public:
  virtual void add() override
  {
    std::cout<<"B::in add"<<std::endl;
  }

  virtual void sub() override
  {
    std::cout<<"B::in sub"<<std::endl;
  }

};


int main()
{
  interface* ass = new A;
  interface* bss = new B;
  B* bss = dynamic_cast<B*>(ass);
  bss->add();
  
}
