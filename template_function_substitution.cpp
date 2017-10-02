#include <iostream>
#include <typeinfo>

using namespace std;

template <typename T> struct wrap {};

template <typename T>
void f_value(T x)
{
    cout << "Type of T is " << typeid(wrap<T>).name() << " , type of x " 
	 << typeid(wrap<decltype(x)>).name() << endl;
}

template <typename T>
void f_cref(const T& x)
{
    cout << "Type of T is " << typeid(wrap<T>).name() << " , type of x " 
	 << typeid(wrap<decltype(x)>).name() << endl;
}

template <typename T>
void f_ref(T& x)
{
    cout << "Type of T is " << typeid(wrap<T>).name() << " , type of x " 
	 << typeid(wrap<decltype(x)>).name() << endl;
}



template <typename T>
void f_refref(T&& x)
{
    cout << "Type of T is " << typeid(wrap<T>).name() << " , type of x " 
	 << typeid(wrap<decltype(x)>).name() << endl;
}

template <typename T>
void f_forward(T&& x)
{
    f_refref(std::forward<T>(x));
}

int main (int argc, char* argv[]) 
{
    int i= 4;
    const int j= 5;
    f_value(i);
    f_value(j);
    f_value(6);
    cout << endl;
    
    f_cref(i);
    f_cref(j);
    f_cref(6);
    cout << endl;
    
    f_ref(i);
    f_ref(j);
    // f_ref(6);
    cout << endl;
    
    f_refref(i);
    f_refref(j);
    f_refref(6);
    cout << endl;
    
    f_forward(i);
    f_forward(j);
    f_forward(6);
    cout << endl;
    
    return 0;
}

