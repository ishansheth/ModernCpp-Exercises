#include <iostream>

using namespace std;

struct iit
{
    iit(int i) : i(i) {}

    bool operator!=(iit that) const { return i != that.i; }
    iit& operator++() { ++i; return *this; }
    iit operator++(int) 
    { 
	iit cp(*this);
	i++; 
	return cp; 
    }

    int operator*() const { return i; }

    int i;
};


struct irange
{
    irange(int b, int e) : b(b), e(e) {}
    iit begin() { return iit(b); }
    iit end() { return iit(e); }

    int b, e;
};


int main (int argc, char* argv[]) 
{
    iit i17(17);
    ++i17;
    i17++;
    cout << "i17++ = " << *(i17++) << endl; 
    cout << "i17 = " << *i17 << endl; 
    cout << "++i17 = " << *(++i17) << endl; 
   
    for (int i : irange(3, 9))
	cout << i << ", ";
    cout << endl;
	
    int array[]= {3, 4, 7, 9, 11};
    // int p= 2;
    // array[p+1]= p+1;

    for (int i= 0; i < sizeof(array)/sizeof(array[0]); ++i)
	cout << array[i] << ", ";
    cout << endl;

    for (int* pi= begin(array); pi < end(array); ++pi)
	cout << *pi << ", ";
    cout << endl;

    for (int a : array)
	cout << a << ", ";
    cout << endl;

    return 0;
}

