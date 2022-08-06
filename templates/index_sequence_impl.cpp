#include <iostream>
#include <type_traits>
#include <tuple>

/*
    Example to print the index sequence values
*/
template<std::size_t...Is>
void print_sequence_impl(std::index_sequence<Is...>)
{
    auto list = std::initializer_list<std::size_t>{Is...};
    for(auto& element : list)
        std::cout<<element<<std::endl;
}

template<std::size_t N>
void print_sequence()
{
    print_sequence_impl(std::make_index_sequence<N>{});
}


template<std::size_t> struct MyIndexSequence;

template<>
struct MyIndexSequence<0>
{
    static constexpr std::size_t value = 0;
};


template<std::size_t N>
struct MyIndexSequence : MyIndexSequence<N-1>
{
    static constexpr std::size_t value = N;
};

int main()
{
    std::cout<<MyIndexSequence<5>::value<<std::endl;
}