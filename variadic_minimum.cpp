#include <iostream>
#include <algorithm>
#include <type_traits>

using namespace std;

template <typename T>
T minimum(const T& x)
{
    return x;
}

// C++14
template <typename First, typename ...Rest>
auto minimum(const First& f, const Rest& ...r)
{
    using type= common_type_t<First, Rest...>;
    return std::min(type(f), type(minimum(r...)));
}

// In C++14
// template <typename ...Types>
// using common_type_t= typename common_type<Types...>::type;



// In C++11
template <typename T>
T minimum11(const T& x)
{
    return x;
}

template <typename First, typename ...Rest>
typename common_type<First, Rest...>::type
minimum11(const First& f, const Rest& ...r)
{
    using type= typename common_type<First, Rest...>::type;
    return std::min(type(f), type(minimum11(r...)));
}



int main (int argc, char* argv[]) 
{
    cout << "minimum(2.5, 7, 4u, 9f) = " << minimum(2.5, 7, 4u, 9.f) << endl;
    cout << "minimum11(2.5, 7, 4u, 9f) = " << minimum11(2.5, 7, 4u, 9.f) << endl;


    return 0;
}

