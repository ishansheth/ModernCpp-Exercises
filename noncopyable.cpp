#include <iostream>


class Noncopy{

protected:
  Noncopy(){}

private:

  Noncopy(const Noncopy&);
  Noncopy& operator=(const Noncopy&);
};


class File: public Noncopy{

public:
  File(){
    std::cout<<"Creating file object"<<std::endl;
  }
};


int main(){
  File f;

  // not allowed
  File f2(f);
}

