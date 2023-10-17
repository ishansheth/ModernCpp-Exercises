#include <iostream>

template<typename T>
auto sum(T& x)
{
  return x;
}

template<typename T, typename...Args>
auto sum(const T& x,Args...args)
{
  return x + sum(args...);
}

class MoveOnly_Point
{
  double x,y;
  public:
  MoveOnly_Point(double mX, double mY):x(mX),y(mY)
  {}
  
  double getX() const { return x;}
  double getY() const { return y;}
  
  void setX(double mx) { x = mx; }
  void setY(double my) { y = my; }
  
  MoveOnly_Point(MoveOnly_Point&& p) = default;
  
  ~MoveOnly_Point()
  {}
};

class CopyOnly_Point
{
  double x,y;
  public:
  CopyOnly_Point(double mX, double mY):x(mX),y(mY)
  {}
  
  double getX() const { return x;}
  double getY() const { return y;}
  
  void setX(double mx) { x = mx; }
  void setY(double my) { y = my; }
  
  CopyOnly_Point(const CopyOnly_Point& p)
  {
    std::cout<<"in copy ctor"<<std::endl;
    x = p.x;
    y = p.y;
  }
  
  ~CopyOnly_Point()
  {}
};


/*
std::pair<double,double> getMidPoint(const CopyOnly_Point& p1, const CopyOnly_Point& p2)
{
  return {(p1.getX() + p2.getX())/2, (p1.getY() + p2.getY())/2};  
}
*/

int main()
{
    auto plus = [value=1](auto...as)
    {
      return value + sum(as...);
    };
    
//    auto functor = [value = 1](auto...as)mutable{return sum(as...);};
    std::cout<<sum(1,2,3)<<std::endl;
    std::cout<<plus(1,2,3)<<std::endl;
    
    CopyOnly_Point p1{1,2};
    CopyOnly_Point p2{p1}; 
    std::cout<<"moving..."<<std::endl;
    // since its a copy only, moving will be done by calling copy ctor
    CopyOnly_Point p3 = std::move(p2);
        
    MoveOnly_Point p10{10,20};
    // since its a move only, copying is disabled, so below line will not compile
    //MoveOnly_Point p20(p10);  

    MoveOnly_Point m1(100,299);    
    MoveOnly_Point m3 = std::move(m1);

}
