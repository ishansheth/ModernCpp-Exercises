#include <iostream>
#include <memory>
#include <cassert>

using namespace std;

class client
{
  std::unique_ptr<int> a;

public:
  client(int z):a(std::make_unique<int>(z))
  {}
  
  client(client&& other):a(std::move(other.a))
  {}

  client& operator=(client&& other)
  {
    if(this != &other)
      a = std::move(other.a);

    return *this;
  }
  
  ~client()=default;
  void print()
  {
    std::cout<<"a:"<<*a<<std::endl;
  }
};

int main (int argc, char* argv[]) 
{
    unique_ptr<int> pempty;
    assert(pempty == nullptr);
    unique_ptr<int> pi(new int);
    *pi= 17;
    const int& piref= *pi;
    cout << "pi = " << *pi << endl; 

    // int* p_danger= pi.get(); 
    // delete p_danger;

    unique_ptr<int> pi2(move(pi));
    cout << "pi2 = " << *pi2 << endl;
    assert(pi == nullptr);

    // shared_ptr<int> si(new int(18));
    shared_ptr<int> si= make_shared<int>(18);
    cout << "si = " << *si << ", use_count = " << si.use_count() << endl;

    auto si2= si;
    cout << "si2 = " << *si2 << ", use_count = " << si.use_count() << endl;

    int* pi3= new int(19);
    shared_ptr<int> si31(pi3), si32(pi3);
    cout << "si31 = " << *si31 << ", use_count = " << si31.use_count() << endl;

    client c1(5);
    client c2 = std::move(c1);
    
    return 0;
}

