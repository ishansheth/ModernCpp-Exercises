#include <iostream>

using namespace std;

namespace preh {

    class complex
    {
      public:
	complex(double re, double im) : re(re), im(im) {}

	// double get_real() const { return re; }
	// double get_imag() const { return im; }

	// void set_real(double r) { re= r; }
	// void set_imag(double i) { im= i; }

	complex& operator+=(const complex& c)
	{
	    // set_real(get_real() + c.get_real());
	    // set_imag(get_imag() + c.get_imag());
	    re+= c.re;
	    im+= c.im;
	    return *this;
	}

	// friend double& imag(complex& c); // #1

	friend double& imag(complex& c) { return c.im; } // #1+#3
	friend const double& imag(const complex& c) { return c.im; } // same as const

	friend double& real(complex& c) { return c.re; } 
	friend const double& real(const complex& c) { return c.re; } 

	// double& imag() { return im; } // #2
      private:
	double re, im;
    };

    // double& imag(complex& c) { return c.im; } // #3

    std::ostream& operator<<(std::ostream& os, const complex& c)
    {
	return os << '(' << real(c) << ',' << imag(c) << ')';
    }

    

}


int main (int argc, char* argv[]) 
{
    preh::complex c(1.2, 3.1), c2(3, 4);
    cout << "Unsere Zahl ist " << c << ".\n";
    // c << cout;
    // std::operator<<(preh::operator<<(std::operator<<(cout, "unsere Zahl ist "), c), ".\n");

    c+= c2;
    cout << "Unsere Zahl ist jetzt " << c << ".\n";

    // c+= 3.4;
    // cout << "Unsere Zahl ist jetzt " << c << ".\n";
    
    imag(c)+= 3.4;
    // c.imag()+= 3.4; // with #2

    return 0;
}

