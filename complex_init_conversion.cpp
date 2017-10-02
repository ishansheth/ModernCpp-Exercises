#include <iostream>

using namespace std;

namespace preh {

    class complex
    {
      public:
	complex(double re, double im) : re(re), im(im) {}
	complex(double re) : complex(re, 0.0) {}

	complex& operator+=(const complex& c)
	{
	    re+= c.re;
	    im+= c.im;
	    return *this;
	}

      private:
	friend double& imag(complex& c) { return c.im; } 
	friend const double& imag(const complex& c) { return c.im; } 

	friend double& real(complex& c) { return c.re; } 
	friend const double& real(const complex& c) { return c.re; } 

	double re;
	double im;
	// double im= 0.0;
    };

    std::ostream& operator<<(std::ostream& os, const complex& c)
    {
	return os << '(' << real(c) << ',' << imag(c) << ')';
    }
}


int main (int argc, char* argv[]) 
{
    preh::complex c(1.2, 3.1), c2(3, 4);
    cout << "Unsere Zahl ist " << c << ".\n";

    c+= 3.4;
    // c+= preh::complex(3.4); // wie darueber
    cout << "Unsere Zahl ist " << c << ".\n";

    return 0;
}

