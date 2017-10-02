#include <iostream>

using namespace std;

namespace preh {

    template <long N>
    struct fibo_alt
    {
	static const long value= fibo_alt<N-1>::value + fibo_alt<N-2>::value;
	// static const long value= N <= 2 ? 1 : fibo_alt<N-1>::value + fibo_alt<N-2>::value;
    };

    template <>
    struct fibo_alt<1>
    {
	static const long value= 1;
    };

    template <>
    struct fibo_alt<2>
      : fibo_alt<1>
    {};

    constexpr long fibo(long n)
    {
	return n <= 2 ? 1 : fibo(n-1) + fibo(n-2);
    }
}


int main (int argc, char* argv[]) 
{
    using namespace preh;

    cout << "fibo_alt<27> = " << fibo_alt<27>::value << endl;

    constexpr long f26= fibo(26); 
    cout << "fibo(26) = " << f26 << endl;
    long n= 25;
    if (argc > 1)
	n= stol(argv[1]);
    cout << "fibo(" << n << ") = " << fibo(n) << endl;
    
    // cout << "fibo_alt<n> = " << fibo_alt<n>::value << endl;
    const int i= 5;
    const int j= n;
    cout << "fibo_alt<i> = " << fibo_alt<i>::value << endl;
    // cout << "fibo_alt<j> = " << fibo_alt<j>::value << endl;

    return 0;
}

