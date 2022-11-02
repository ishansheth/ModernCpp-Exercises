#include <iostream>
#include <type_traits>

template<typename T>
void print_type_info(const T& value)
{
    if (std::is_integral<T>::value)
        std::cout<<"its an integral type\n";
    else
        std::cout<<"its not an integral type\n";
}

template<typename T>
auto increament_volume(const T& value)
{
    if constexpr(std::is_integral<T>::value)
        return value + 1;
    else
        return value + 0.1;
}


int main()
{
    print_type_info(5);
    print_type_info(5.3);

    std::cout<<increament_volume(3)<<std::endl;
}