#include <iostream>
#include <vector>
#include <numeric>

template<typename T>
concept Printable = requires(std::ostream& os, const T& msg)
{
  {os<<msg};
};

template<typename T>
concept integralT = std::is_integral_v<T>;


template<typename T>
concept NumericType = requires(T param)
{
  requires std::is_integral_v<T> || std::is_floating_point_v<T>;
  requires !std::is_same_v<bool,T>;
  requires std::is_arithmetic_v<decltype(param+1)>;
};

template<typename T>
concept PointerType = requires(T param)
{
  requires std::is_pointer_v<T>;
  param != nullptr;
};

template<Printable T>
void prinT(const T& val)
{
  std::cout<<val<<std::endl;
}


template<typename T>
requires NumericType<T>
T add_one(const T val)
{
  return val+1;
}

template<typename T>
requires PointerType<T>
auto add_one(const T val)
{
  return add_one(*val);
}

class Shape
{
  private:
    virtual void print(std::ostream& os) const = 0;     

  public:
    virtual void draw() const = 0;
  
    friend std::ostream& operator<<(std::ostream& os, const Shape& sh)
    {
      sh.print(os); 
      return os;
    }
  
};


class Rectangle : public Shape
{
  private:
    void print(std::ostream& os) const override
    {
      os<<"its a rectangle"<<std::endl;
    }
    
  public:
    void draw() const override
    {
      std::cout<<"drawing a rectangle"<<std::endl;
    }

};

template<typename T>
concept ShapeInterface = requires(T param)
{
  {param.draw()}->std::same_as<void>;
  {std::cout<<param}->std::convertible_to<std::ostream&>;
};


template<typename T>
requires ShapeInterface<T>
void draw_shape(const T& param)
{
  param.draw();
}

template<typename T>
requires ShapeInterface<T>
void print_shape(const T& param)
{
  std::cout<<param<<std::endl;
}


template<typename T>
void clever_swap(T& a, T& b)
{
  constexpr bool has_member_swap = requires (T a, T b)
  {
    a.swap(b);
  };
  
  if constexpr(has_member_swap)
  {
    a.swap(b);
  }
  else
  {
    using std::swap;
    swap(a,b);
  }
}

template<typename T>
struct Wrapper
{
  constexpr static bool value = requires (typename T::value_type x){++x;};
};

int main()
{ 
  int x = 10;
  int y = 20;
  std::cout<<add_one(1)<<std::endl; 
  std::cout<<add_one(&x)<<std::endl; 
  
  Shape* pShape = new Rectangle();
  draw_shape(*pShape);
  print_shape(*pShape);
  
  static_assert(integralT<unsigned int>,"integralT concept failed");
  std::cout<<Wrapper<int>::value<<std::endl;  
  
}

