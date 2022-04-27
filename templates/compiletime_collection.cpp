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
*/

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

}