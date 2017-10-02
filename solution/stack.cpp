#include <iostream>
#include <memory>
#include <exception>
#include <cassert>
#include <initializer_list>
#include <utility>

// Stack-Implementierung
// mit Move-Operationen
// und Kopie
// mit Initializer-Liste

namespace preh {

    // Immer gut, von std::exception abzuleiten
    struct underflow
      : std::exception
    {
	const char* what() const noexcept {return "Stack underflow!\n";}
    };

    struct overflow
      : std::exception
    {
	const char* what() const noexcept {return "Stack overflow!\n";}
    };

    class stack
    {
	void check_empty() const
	{
	    if (empty())
		throw underflow{};
	}
	
	void check_full() const
	{
	    if (full())
		throw overflow{};
	}
	
      public:
	stack(int s= 50)
	  : my_size(s), pos(-1), data(new int[s])
	{}

	stack(std::initializer_list<int> il)
	  : my_size(il.size()), pos(my_size-1), data(new int[my_size])
	{
	    // initializer_list und unique_ptr<[]> haben dummerweise verschiedene Interfaces
	    int i= 0;
	    for (auto&& v : il)
		data[i++]= v;
	}

	// Wird nicht generiert, weil unique_ptr keinen Copy-Konstruktor hat
	stack(const stack& that)
	  : my_size(that.my_size), pos(that.pos), data(new int[my_size])
	{
	    for (int i= 0; i <= pos; ++i)
		data[i]= that.data[i];
	}

	// Besser selbst implementieren, weil pos und my_size sonst bleiben
	stack(stack&& that)
	  : my_size(that.my_size), pos(that.pos), data(std::move(that.data))
	{
	    that.my_size= 0;
	    that.pos= -1;
	}
	    
	// destructor by default

	stack& operator=(const stack& that)
	{
	    if (that.pos >= my_size)
		throw overflow{};
	    pos= that.pos;
	    for (int i= 0; i <= pos; ++i)
		data[i]= that.data[i];
	    return *this;	    
	}

	stack& operator=(stack&& that)
	{
	    std::swap(my_size, that.my_size);
	    std::swap(pos, that.pos);
	    std::swap(data, that.data);
	    return *this;
	}
	
	int top() const
	{
	    check_empty();
	    return data[pos];
	}

	void pop()
	{
	    check_empty();
	    --pos;
	}

	void push(int item)
	{
	    check_full();
	    data[++pos]= item;
	}

	void clear() noexcept
	{
	    pos= -1;
	}

	int size() const noexcept { return pos + 1; }

	bool full() const noexcept { return pos == my_size - 1; }

	bool empty() const noexcept { return pos == -1; }

	// Free friend function
	friend std::ostream& operator<<(std::ostream& os, const stack& s)
	{
	    os << "[";
	    for (int i= s.pos; i >= 0; --i) {
		os << s.data[i];
		if (i > 0)
		    os << ":";
	    }
	    return os << "]";
	}
	
      private:
	int                    my_size, pos;
	std::unique_ptr<int[]> data;
    };

}


int main (int argc, char* argv[]) 
{
    using namespace std;
    using namespace preh;

    stack   si(100);

    assert(si.empty());
    assert(!si.full());
    assert(si.size() == 0);
    
    for (int i= 0; i < 100; ++i)
	si.push(i);

    assert(!si.empty());
    assert(si.full());
    assert(si.size() == 100);
    assert(si.top() == 99);
    
    si.pop();
    assert(!si.empty());
    assert(!si.full());
    assert(si.size() == 99);
    assert(si.top() == 98);

    stack   si2= {3, 9, 4, 8};
    cout << "si2 initial = " << si2 << endl;

    auto si3(move(si2));
    cout << "si3 nach Move-Konstruktor = " << si3 << endl;

    auto si4(si3);
    cout << "si3 nach Copy-Konstruktor = " << si3 << endl;
    cout << "si4 nach Copy-Konstruktor = " << si4 << endl;
    
    return 0;
}

