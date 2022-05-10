/*
resources:

https://aherrmann.github.io/programming/2016/02/28/unpacking-tuples-in-cpp14/
https://www.fluentcpp.com/2019/03/08/stl-algorithms-on-tuples/

*/

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

// executes an functor on the every element of tuple
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

// applies the functor to the every element of the tuple and returns a new one with its result
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

// takes first N elements from tuple, creates a new one and returns it
template<typename T,std::size_t...Is>
auto take_front_impl(T&& tuple,std::index_sequence<Is...>)
{
    auto res = std::make_tuple(std::get<Is>(tuple)...);
    return res;
}

template<std::size_t N,typename T>
auto take_front(T&& tuple)
{
    return take_front_impl(std::forward<T>(tuple),std::make_index_sequence<N>{});
}



template <class F, std::size_t... Is>
constexpr auto index_apply_impl(F f,
                                std::index_sequence<Is...>) {
    return f(std::integral_constant<std::size_t,Is>{}...);
}

template <size_t N, class F>
constexpr auto index_apply(F f) {
    return index_apply_impl(f, std::make_index_sequence<N>{});
}


template<std::size_t N,typename T>
auto take_frontC14(T&& tuple)
{
    return index_apply<N>(
        [&](auto... Is) 
        {
            return std::make_tuple(std::get<Is>(tuple)...);
        });
}


int main()
{
    auto t1 = std::make_tuple(1,"str",1.5f);
    for_each(t1,[](auto x){std::cout<<"Value:"<<x<<std::endl;});

    auto t2 = std::make_tuple(1,2.0,1.5f); 
    auto t3 = transform(t2,[](auto x){return x+1;});
    for_each(t3,[](auto x){std::cout<<"Value:"<<x<<std::endl;});

    auto t4 = std::make_tuple(1,3.4,'a',"ishan");
    auto t5 = take_front<2>(t4);
    std::cout<<std::get<0>(t5)<<','<<std::get<1>(t5)<<std::endl;

    auto t6 = take_frontC14<2>(t4);
    std::cout<<std::get<0>(t6)<<','<<std::get<1>(t6)<<std::endl;

}
