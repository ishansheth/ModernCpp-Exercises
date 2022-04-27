
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <array>
#include <vector>
#include <cstring>
#include <tuple>

using namespace std;

char g_payload[10*1024];

struct Header
{
    int identifier;
    std::array<uint8_t,8> payload;

    Header(const int& x, const std::array<uint8_t,8>& pl):identifier(x),payload(pl)
    {}
};

template <typename T>
T minimum(const T& x)
{
    return x;
}

// C++14 : function return type can be auto 
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

/*
    Example:
        pass variable numbers of parameters to a function
        function checks the validity of the parameters:
        -    get the parameters and pass it to helper function as tuple
        -    helper function gets pair of elements out of tuple and checks them
        -    helper function checks it for the consecutive pair of elements of tuple by recursion, accumulates the results
             and returns it 
*/

void createPayload()
{
    std::vector<Header> dest;
    for(uint8_t i = 0; i < 10; i++)
    {
        dest.emplace_back((i+1)*10,std::array<uint8_t,8>{0,0,0,0,0,0,0,0});        
    }
    memcpy(g_payload,dest.data(),dest.size()*sizeof(Header));
}

bool checkHeader(unsigned index, Header& h)
{
    if(index == h.identifier)
        return true;
    else
        return false;
}

template<int N1,typename T,typename...Args>
typename std::enable_if< N1 == (sizeof...(Args)),bool>::type checkSingleStructs(T& t)
{
    return true;
}

template<int N1,typename T,typename...Args>
typename std::enable_if< (N1+1) <= (sizeof...(Args)-1),bool>::type checkSingleStructs(T& t)
{
    auto a = std::get<N1>(t);
    auto b = std::get<N1+1>(t);
    bool result = checkHeader(a,b);

    result = result && checkSingleStructs<N1+2,T,Args...>(t);
    return result;
}

template<typename...Args>
void checkPayload(Args&&...args)
{
    auto arg_tuple = std::make_tuple(args...);
    auto res = checkSingleStructs<0,decltype(arg_tuple),Args...>(arg_tuple);

    if(res)
        std::cout<<"It matches"<<std::endl;
    else
        std::cout<<"It doesnt match"<<std::endl;

}

int main (int argc, char* argv[]) 
{
    cout << "minimum(2.5, 7, 4u, 9f) = " << minimum(2.5, 7, 4u, 9.f) << endl;
    cout << "minimum11(2.5, 7, 4u, 9f) = " << minimum11(2.5, 7, 4u, 9.f) << endl;

    Header h1 = {1,std::array<uint8_t,8>{0,0,0,0,0,0,0,0}};
    Header h2 = {2,std::array<uint8_t,8>{0,0,0,0,0,0,0,0}};

    checkPayload(1,h1,3,h2);

    return 0;
}

