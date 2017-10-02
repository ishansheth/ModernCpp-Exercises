#include <iostream>
#include <cmath>
#include <exception>

using namespace std;

struct root_of_negative
  : std::runtime_error
{
    root_of_negative() 
      : std::runtime_error("Root of negative number") {}
};

namespace preh {

    int root_of(double x, double& res) noexcept
    {
	// try {
	//     throw root_of_negative();
	// } catch(...) {}
	    
	if (x < 0) 
	    return 1;
	res= sqrt(x);
	return 0;
    }

    double root(double x) 
    {
	throw root_of_negative();
	return sqrt(x);
    }
    
}


int main (int argc, char* argv[]) 
{
    using namespace preh;

    double x;
    int error_code= root_of(-9.0, x);
    if (error_code != 0)
	cout << "Och noe.\n";
    else
	cout << "x ist " << x << endl;

    try {
	double res= root(-9);
	cout << "root(-9) = " << res << endl;
    } catch (std::runtime_error& r) {
	cout << r.what() << endl;
    }

    return 0;
}

