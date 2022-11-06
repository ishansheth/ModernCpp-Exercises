#include <vector>
#include <atomic>
#include <memory>
#include <iostream>
#include <list>

// https://medium.com/@vgasparyan1995/what-is-an-allocator-c8df15a93ed

std::atomic_int g_counter{0};

template<typename T>
class MyAllocator : public std::allocator<T>
{
    private:
        using Base = std::allocator<T>;
        using Pointer = typename std::allocator_traits<Base>::pointer;
        using SizeType = typename std::allocator_traits<Base>::size_type;

    public:
    MyAllocator() = default;

    template<typename U>
    MyAllocator(const MyAllocator<U>& other)
    : Base(other)
    {}

    template<typename U>
    struct rebind
    {
        using other = MyAllocator<U>;
    };

    Pointer allocate(std::size_t n)
    {
        g_counter.fetch_add(n*sizeof(T));
        return Base::allocate(n);
    }

    void deallocate(Pointer p,SizeType n)
    {
        g_counter.fetch_sub(n*sizeof(T));
        Base::deallocate(p,n);
    }
};


template<template<typename T,typename Alloc> typename ContainerT>
void test()
{
    std::cout<<"memory usage before:"<<g_counter.load()<<std::endl;
    ContainerT<int, MyAllocator<int>> container;
    for(int i = 0; i < 10; i++)
        container.insert(std::end(container),i);

    std::cout<<"memory usage after:"<<g_counter.load()<<std::endl;
}

int main()
{
    test<std::vector>();
    test<std::list>();

}