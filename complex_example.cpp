#include <iostream>


class complex
{
private:
	double real,imag;

	public:
	
	complex(double x,double y): real(x),imag(y)
	{}
	
	double get_real() const
	{
		return real;
	}
		
	double get_imag() const
	{
		return imag;	
	}
	
	friend std::ostream& operator<<(std::ostream& os, const complex& c)
	{
		return os << "(" << c.real << "," << c.imag << ")" << std::endl;
	}
	
};


//std::ostream& operator<<(std::ostream& os, const complex& c)
//{
//	return os << "(" << c.get_real() << "," << c.get_imag() << ")" << std::endl;
//}

int main(int argc, char* argv[])
{
	complex c(2,3);
	std::cout << c;
}