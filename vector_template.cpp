#include <iostream>
#include <exception>
#include <initializer_list>
#include <algorithm>
#include <memory>
#include <typeinfo>

namespace preh {

    struct out_of_range : std::runtime_error
    {	out_of_range() : std::runtime_error("Index out of range.") {}    };

    template <typename Value>
    class vector
    {
	void index_check(unsigned i) const { if (i >= my_size) throw out_of_range(); }
      public:
	explicit vector(unsigned s) : my_size(s), data(new Value[my_size]) { std::cout << "s-ctor\n"; }

	vector(std::initializer_list<Value> il) : my_size(il.size()), data(new Value[my_size])
	{
	    unsigned i= 0;
	    for (Value v : il) 
		data[i++]= v;       
	}

	vector(const vector& that)
	  : my_size(that.my_size), data(new Value[my_size])
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


	Value&       operator[](unsigned int i) &      { index_check(i); return data[i]; }
	const Value& operator[](unsigned int i) const& { index_check(i); return data[i]; }

	unsigned size() const { return my_size; }

	// private:
	unsigned                 my_size;
	std::unique_ptr<Value[]>  data;
    };

    template <typename Value1, typename Value2>
    auto operator+(const vector<Value1>& x, const vector<Value2>& y)
	-> vector< decltype(x[0] + y[0]) >
    {
	vector< decltype(x[0] + y[0]) > result(x.size());
	for (unsigned i= 0; i < x.size(); ++i)
	    result[i]= x[i] + y[i];
	return result;
    }

    template <typename Value>
    std::ostream& operator<<(std::ostream& os, const vector<Value>& v)
    {
	os << '[';
	if (v.size() > 0)
	    os << v[0];
	for (unsigned i= 1; i < v.size(); ++i)
	    os << ',' << v[i];
	return os << ']';
    }

    template <typename Value>
    void move_only(vector<Value>&& v)
    {
	std::cout << "Ich bin die move-only-Funktion.\n";
    }

}

using namespace std;

int main (int argc, char* argv[]) 
{
    preh::vector<double> w= {3, 5, 9, 2}, x(w);
    cout << "w = " << w << endl;
    preh::vector<double> y= {1, 3, 5, 2}, z(4);
    z= w + y;
    cout << "z = " << z << endl;
    move_only(w + y);
    // move_only(w);

    preh::vector<double> a= w + y; // Summe wird gleich in a geschrieben, ohne copy oder move
    cout << "a = " << a << endl;

    preh::vector<unsigned> vu= {3u, 2u, 7u};
    preh::vector<short>    vs= {-6, 7, 2};
    cout << "vu + vs = " << vu + vs << endl;
    cout << "Type is " << typeid(vu + vs).name() << endl;

    // Ab C++17
#if __cplusplus >= 201703L
    preh::vector vd= {3.f, 2.9f, 7.1f};
    cout << "vd = " << vd << endl;
    cout << "Type is " << typeid(vd).name() << endl;
#endif
}

 
