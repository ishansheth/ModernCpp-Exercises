#include <iostream>

using namespace std;

namespace preh {

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
}


int main (int argc, char* argv[]) 
{
    using namespace preh;

    constexpr double sq3= square_d(3.0);
    constexpr double sq4= square(4.0);

    cout << "popcount(0x11000) = " << popcount(0x11000) << endl;
    cout << "popcount(0b11000110001101110000) = " << popcount(0b1100'0110'0011'0111'0000ull) << endl;

    return 0;
}

