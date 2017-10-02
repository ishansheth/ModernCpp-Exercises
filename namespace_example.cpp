#include <iostream>
#include <cmath>
#include <exception>

using namespace std;

namespace preh {


    double root(double x) 
    {
	return sqrt(x);
    }

    namespace intern {
	double square(double x) { return x*x; }
	double f(double x) { return root(x); }

	struct dings {};
	void print(const dings&) { std::cout << "print dings.\n"; }
    }
    
}


int main (int argc, char* argv[]) 
{
    using preh::root;
    using preh::intern::square;

    double x= 7.3;
    cout << "square(x) = " << square(x) << endl;

    cout << "f(17) = " << preh::intern::f(17) << endl;

    preh::intern::dings d;
    print(d);

    return 0;
}

