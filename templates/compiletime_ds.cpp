/*
Structure to store compiletime objects 
https://www.fluentcpp.com/2018/11/02/variable-number-compile-time/
*/

#include <iostream>
#include <tuple>
#include <vector>

template<int k> struct Simplex { void print(){ std::cout << k << '\n';} };

template<std::size_t n>
class SimplexStorage
{
        template<std::size_t ... ks>
        using StorageImpl = std::tuple<Simplex<ks>...>;

        template<std::size_t ... ks>
        static StorageImpl<(1+ks)...> make_storage(std::index_sequence<ks...>)
        {
            return StorageImpl<(1+ks)...>{};
        }

        using Storage = decltype(make_storage(std::make_index_sequence<n>{}));

        Storage storage_;

    public:

        template<int k>
        Simplex<k>& getSimplexes()
        {
            // since its k-1, the indexing starts from 1,2,3,.....
            return std::get<k-1>(storage_);
        }
};

/*
https://www.fluentcpp.com/2017/06/02/write-template-metaprogramming-expressively/

https://stackoverflow.com/questions/27687389/how-does-void-t-work

Example of a meta function
*/

/* this is essentially a void_t from C++17*/
template<typename...>
using try_to_instantiate = void;

template<typename T, typename = void>
struct is_incrementable : std::false_type
{};

template<typename T>
struct is_incrementable<T,  try_to_instantiate< decltype(++std::declval<T&>()) >>: std::true_type
{};

constexpr std::size_t sample_func()
{
    return 10;
}

/*
    Another example of compile time collection using tuples and varaidc templates
    https://stackoverflow.com/questions/27941661/generating-one-class-member-per-variadic-template-argument
*/

template<typename T1, typename T2>
struct SameType
{
    static const bool value = false;
};

template<typename T>
struct SameType<T,T>
{
    static const bool value = true;
};

template<typename...Types>
class FantasticCollection
{
    using vtype = std::tuple<std::vector<Types>...>;
    vtype m_collection;

    public:

    template<int N, typename T>
    struct VectorOfType : SameType<T, typename std::tuple_element<N,vtype>::type::value_type>
    {};

    template <int N, class T, class Tuple,bool Match>
    struct MatchingField
    {
        static std::vector<T>& get(Tuple& tp)
        {
            // The "non-matching" version, recursively call the get function of
            return MatchingField<N+1, T, Tuple,VectorOfType<N+1, T>::value>::get(tp);
        }
     };

    template <int N, class T, class Tuple>
    struct MatchingField<N, T, Tuple, true>
    {
        static std::vector<T>& get(Tuple& tp)
        {
            return std::get<N>(tp);
        }
    };

    template <typename T>
    std::vector<T>& get()
    {
        return MatchingField<0, T, vtype,VectorOfType<0, T>::value>::get(m_collection);
    }
};


template<std::size_t idx,typename...Rest>
struct GetHelper{};

template<typename...T>
struct DataStructure
{};

template<typename T,typename...Rest>
struct DataStructure<T,Rest...>
{
    T first;
    DataStructure<Rest...> rest;

    DataStructure(const T& f, const Rest&...r):first(f),rest(r...)
    {}

    template<std::size_t idx>
    auto get()
    {
        return GetHelper<idx,DataStructure<T,Rest...>>::get(*this);
    }
};

template<typename T, typename...Rest>
struct GetHelper<0,DataStructure<T,Rest...>>
{
    static T get(DataStructure<T,Rest...>& data)
    {
        return data.first;
    }
};

template<std::size_t idx,typename T, typename...Rest>
struct GetHelper<idx,DataStructure<T,Rest...>>
{
    static auto get(DataStructure<T,Rest...>& data)
    {
        return GetHelper<idx-1,DataStructure<Rest...>>::get(data.rest);
    }
};


int main()
{
    SimplexStorage<sample_func()> storage_collection;
    storage_collection.getSimplexes<1>().print();
    storage_collection.getSimplexes<2>().print();
    storage_collection.getSimplexes<3>().print();
    storage_collection.getSimplexes<4>().print();
    storage_collection.getSimplexes<5>().print();

    std::cout<<"If int incrementable:"<<is_incrementable<int>::value<<std::endl;
    std::cout<<"If string incrementable:"<<is_incrementable<std::string>::value<<std::endl;

    FantasticCollection<int,float,std::string> a;
    auto vec = a.get<float>();
    vec.push_back(2.5f);

    DataStructure<int, float, std::string> data(1, 2.1, "Hello");
        
    std::cout << data.get<0>() << std::endl;
    std::cout << data.get<1>() << std::endl;
    std::cout << data.get<2>() << std::endl;

}