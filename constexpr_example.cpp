#include <iostream>
#include <limits>
#include <cstring>
#include <cmath>

using namespace std;


    constexpr double square_d(double x)
    {
	return x * x;
    }

    template <typename T>
    constexpr T square(const T& x)
    {
	return x * x;
    }

    // Ab C++14
    constexpr size_t popcount(size_t x)
    {
	int count= 0;
	for( ; x != 0; ++count)
	    x&= x - 1;

	// for( ; x != 0; x >>= 1)
	//     if (x & 1)
	// 	count++;
	return count;
    }

  class Exam
  {
    int points;
  public:
    constexpr Exam(int a): points(a){}
    int getPoints() const { return points; }
  };

  template<typename T = std::uint32_t>
  T constexpr14_bin(const char* t)
  {
    T x = 0;
    std::size_t b = 0;
    int base = 1;

    for(int i = strlen(t)-1; i >= 0 ; i--)
      {
	if(b > std::numeric_limits<T>::digits)
	  throw std::overflow_error("Too many bits");
	
	if(t[i] == '1')
	  {
	    x += base;
	    b++;
	  }
	base = base * 2;
      }
    return x;
  }
  


int main (int argc, char* argv[]) 
{

    constexpr double sq3= square_d(3.0);
    constexpr double sq4= square(4.0);

    cout << "popcount(0x11000) = " << popcount(0x11000) << endl;
    cout << "popcount(0b11000110001101110000) = " << popcount(0b1100'0110'0011'0111'0000ull) << endl;

    constexpr Exam e = Exam(100);
    std::cout<<e.getPoints()<<std::endl;

    std::cout<<constexpr14_bin("111")<<std::endl;
    std::cout<<constexpr14_bin("101")<<std::endl;
    std::cout<<constexpr14_bin("100")<<std::endl;
    std::cout<<constexpr14_bin("001")<<std::endl;
    
    return 0;
}

