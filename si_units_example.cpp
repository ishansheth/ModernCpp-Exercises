/*
this example is from the book C++ Programming by Bjarne Stroustrup
*/

#include <iostream>

template<int M,int K,int S>
struct Unit
{
  enum {m=M,kg=K,s=S};
};

template<typename U1,typename U2>
struct Uplus
{
  using type = Unit<U1::m+U2::m,U1::kg+U2::kg,U1::s+U2::s>;
};

template<typename U1,typename U2>
using Unit_plus = typename Uplus<U1,U2>::type;

template<typename U1,typename U2>
struct Uminus
{
  using type = Unit<U1::m-U2::m,U1::kg-U2::kg,U1::s-U2::s>;
};

template<typename U1,typename U2>
using Unit_minus = typename Uminus<U1,U2>::type;

template<typename U>
struct Quantity
{
  double val;
  explicit constexpr Quantity(double d):val{d}{}
};

using M = Unit<1,0,0>;  //meters
using Kg = Unit<0,1,0>;  //kilograms
using S = Unit<0,0,1>;  //seconds

template<typename U>
Quantity<U> operator+(Quantity<U> x,Quantity<U> y)
{
  return Quantity<U>{x.val+y.val};
}

template<typename U>
Quantity<U> operator-(Quantity<U> x,Quantity<U> y)
{
  return Quantity<U>{x.val-y.val};
}

template<typename U1,typename U2>
Quantity<Unit_plus<U1,U2>> operator*(Quantity<U1> x,Quantity<U2> y)
{
  return Quantity<Unit_plus<U1,U2>>{x.val*y.val};
}

template<typename U1,typename U2>
Quantity<Unit_minus<U1,U2>> operator/(Quantity<U1> x,Quantity<U2> y)
{
  return Quantity<Unit_minus<U1,U2>>{x.val/y.val};
}

template<typename U>
std::ostream& operator<<(std::ostream& os,Quantity<U>& x)
{
  os << x.val;
  return os;
}

// user defined literals
constexpr Quantity<M> operator""_m(long double d){return Quantity<M>{d};}
constexpr Quantity<Kg> operator""_kg(long double d){return Quantity<Kg>{d};}
constexpr Quantity<S> operator""_s(long double d){return Quantity<S>{d};}

constexpr Quantity<M> operator""_km(long double d){return Quantity<M>{d*1e3};}
constexpr Quantity<Kg> operator""_g(long double d){return Quantity<Kg>{d/1e3};}
constexpr Quantity<Kg> operator""_mg(long double d){return Quantity<Kg>{d/1e6};}
constexpr Quantity<S> operator""_ms(long double d){return Quantity<S>{d/1e3};}
constexpr Quantity<S> operator""_us(long double d){return Quantity<S>{d/1e6};}
constexpr Quantity<S> operator""_ns(long double d){return Quantity<S>{d/1e9};}



int main()
{
  Quantity<M> x1{10.9};
  Quantity<M> x2{1.9};

  auto x3 = x1+x2;
  std::cout<<x3<<std::endl;

  auto distance = 10.9_m;
  auto time = 20.5_s;
  auto speed = distance/time;

  std::cout<<"speed:"<<speed<<std::endl;
  
}
