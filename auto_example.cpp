#include <iostream>
#include <cmath>

using namespace std;

namespace preh {

    int divide(int a, int b) {
	return a / b;
    }

    float divide(float a, float b) {
	return std::floor(a / b);
    }

    int& my_int() // Referenzrueckgabe nur zu Demozwecken
    {
	static int i= 0;
	++i; 
	return i;
    }

    template <typename Value> struct vector {};

}


int main (int argc, char* argv[]) 
{
    using namespace preh;

    auto c= divide(7, 3);
    cout << "c = " << c << ".\n";

    const auto& i1= my_int();
    my_int(); my_int(); my_int();
    
    // i1++;
    cout << "i1 = " << i1 << endl;

    decltype(divide(7, 3)) c2= divide(7, 3);
    preh::vector<decltype(divide(7, 3))>  vd;

    decltype(auto) i2= my_int(); // C++17
    i2++; // Auweiha, aendert i in my_int

    return 0;
}

