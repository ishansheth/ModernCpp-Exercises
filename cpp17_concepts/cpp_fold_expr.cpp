#include <iostream>

template<typename...T>
auto sum(T&&...values)
{
    typename std::common_type_t<T...> result;
    (void)std::initializer_list<int>{(result += values,0)...};
    return result;
}

template<typename...T>
auto sum2(T&&...values)
{
    // with fold expression
    return (values + ...);
}

template<typename...T>
auto avg(T&&...values)
{
    // with fold expression
    return (values + ...) / sizeof...(values);
}


int main()
{
    std::cout<<sum2(1,2,3.f,4.5)<<std::endl;
    std::cout<<avg(1,2,3.f,4.5)<<std::endl;

}