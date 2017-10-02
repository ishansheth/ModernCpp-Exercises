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
}


int main (int argc, char* argv[]) 
{
    using namespace preh;

    cout << "divide(5, 3) = " << divide(5, 3) << endl;
    cout << "divide(5.f, 3.f) = " << divide(5.f, 3.f) << endl;
    // cout << "divide(5.f, 3) = " << divide(5.f, 3) << endl;
    // cout << "divide(5., 3.) = " << divide(5., 3.) << endl;

    return 0;
}

