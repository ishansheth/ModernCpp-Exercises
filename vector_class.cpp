#include <iostream>
#include <exception>
#include <initializer_list>
#include <algorithm>
#include <memory>

namespace preh {

    struct out_of_range : std::runtime_error
    {	out_of_range() : std::runtime_error("Index out of range.") {}    };

    class vector
    {
	void index_check(unsigned i) const { if (i >= my_size) throw out_of_range(); }
      public:
	explicit vector(unsigned s) : my_size(s), data(new double[my_size]) { std::cout << "s-ctor\n"; }

	vector(std::initializer_list<double> il) : my_size(il.size()), data(new double[my_size])
	{
	    unsigned i= 0;
	    for (double v : il) 
		data[i++]= v;       
	}

	vector(const vector& that)
	  : my_size(that.my_size), data(new double[my_size])
	{
	    std::copy(&that.data[0], &that.data[my_size], &data[0]);
	    std::cout << "cp-ctor\n";
	}

	vector(vector&& that)
	  : my_size(that.my_size)
	{
	    std::swap(data, that.data);
	    that.my_size= 0;
	    std::cout << "mv-ctor\n";	   
	}

	vector& operator=(const vector& that)
	{
	    std::copy(&that.data[0], &that.data[my_size], &data[0]);
	    std::cout << "cp-asgm\n";	   
	    return *this;
	}

	vector& operator=(vector&& that)
	{
	    std::swap(data, that.data);
	    that.my_size= 0;
	    std::cout << "mv-asgm\n";	   
	    return *this;
	}


	double&       operator[](unsigned int i) &      { index_check(i); return data[i]; }
	const double& operator[](unsigned int i) const& { index_check(i); return data[i]; }

	unsigned size() const { return my_size; }

	// private:
	unsigned                 my_size;
	std::unique_ptr<double[]>  data;
    };

    vector operator+(const vector& x, const vector& y)
    {
	vector result(x.size());
	for (unsigned i= 0; i < x.size(); ++i)
	    result[i]= x[i] + y[i];
	std::cout << "Address of sum = " << std::hex << result.data.get() << '\n';
	return result;
    }

    std::ostream& operator<<(std::ostream& os, const vector& v)
    {
	os << '[';
	if (v.size() > 0)
	    os << v[0];
	for (unsigned i= 1; i < v.size(); ++i)
	    os << ',' << v[i];
	return os << ']';
    }

    double dot(const vector& v, const vector& w)
    {
	double res= 0.0;
	for (unsigned i= 0; i < v.size(); ++i)
	    res+= v[i] * w[i];
	return res;
    }

    void move_only(vector&& v)
    {
	std::cout << "Ich bin die move-only-Funktion.\n";
    }

}

using namespace std;

int main (int argc, char* argv[]) 
{
    preh::vector v(7);
    v[2]= 9;
    cout << "v[2] = " << v[2] << endl;
    cout << "v = " << v << endl;
    // preh::vector(3)[2]= 11; // Quatsch

    // cout << "dot(4, 4) = " << preh::dot(4, 4) << endl;
    // preh::vector w= 9;

    preh::vector w= {3, 5, 9, 2}, x(w);
    w[2]= 11;
    cout << "w = " << w << endl;
    cout << "x = " << x << endl;
    preh::vector y= {1, 3, 5, 2}, z(4);
    z= w + y;
    cout << "z = " << z << endl;
    std::cout << "Address of z = " << std::hex << z.data.get() << '\n';
    move_only(w + y);
    // move_only(w);

    std::move(z);
    cout << "z = " << z << endl;  

    x= std::move(z);
    cout << "x = " << x << endl;
    cout << "z = " << z << endl;

    preh::vector a= w + y; // Summe wird gleich in a geschrieben, ohne copy oder move
    cout << "a = " << a << endl;
    std::cout << "Address of a = " << std::hex << a.data.get() << '\n';  
}

