#include <iostream>
#include <tuple>
#include <vector>

template<typename T>
T increment_one(const T& val)
{
    return val+1;
}


template<typename T>
void printValue(const T& val)
{
    std::cout<<val<<std::endl;
}


template<typename T,typename Func,std::size_t...Is>
void for_each_impl(T&& t1, Func&& f, std::index_sequence<Is...>)
{
    (void)std::initializer_list<unsigned int>{ (std::forward<Func>(f)( std::get<Is>(t1) ),(unsigned int)Is)... };
}

template<typename T,typename Func>
void for_each(T&& tuple,Func&& f)
{
    for_each_impl(std::forward<T>(tuple),std::forward<Func>(f),
    std::make_index_sequence< std::tuple_size< std::remove_reference_t<T> >::value>{});
}

template<typename T,typename Func,std::size_t...Is>
auto transform_impl(T&& t1, Func&& f, std::index_sequence<Is...>)
{
    return std::make_tuple(std::forward<Func>(f)( std::get<Is>(t1))...);
}

template<typename T,typename Func>
auto transform(T&& tuple, Func&& f)
{
    return transform_impl(std::forward<T>(tuple),std::forward<Func>(f),
    std::make_index_sequence< std::tuple_size< std::remove_reference_t<T> >::value>{});
}

int main()
{

    auto t1 = std::make_tuple(1,"str",1.5f);
    for_each(t1,[](auto x){std::cout<<"Value:"<<x<<std::endl;});

    auto t2 = std::make_tuple(1,2.0,1.5f);
    auto t3 = transform(t2,[](auto x){return x+1;});
    for_each(t3,[](auto x){std::cout<<"Value:"<<x<<std::endl;});
}
