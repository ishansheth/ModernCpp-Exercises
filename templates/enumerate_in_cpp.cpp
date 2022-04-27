#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

template<typename Iter>
class MyItertaor
{
    Iter m_iter;
    std::size_t m_cnt;
    
    public:
    MyItertaor(Iter a):m_iter(a),m_cnt(0)
    {}
    
    
    bool operator!=(const MyItertaor& that)
    {
        return m_iter != that.m_iter;
    }
    
    std::pair<std::size_t,decltype(*m_iter)> operator*()
    {
        return {m_cnt,*m_iter};        
    }
    
    MyItertaor& operator++()
    {
        ++m_iter;
        m_cnt++;
        return *this;
    }
};


template<typename T>
class MyContainer
{
    std::vector<T> m_container;
    std::size_t m_size;
    std::size_t m_cnt;
    
    public:
    
    template<typename U>
    MyContainer(const std::initializer_list<U>& elements): m_container{elements},m_cnt(0),m_size(m_container.size())
    {}
    
    using IteratorType = decltype(m_container.begin());
   
    
    MyItertaor<IteratorType> begin()
    {
        std::cout<<"in begin"<<std::endl;
        return MyItertaor<IteratorType>(m_container.begin());
    }
    
    MyItertaor<IteratorType> end()
    {
        std::cout<<"in end"<<std::endl;
        return MyItertaor<IteratorType>(m_container.end());
    }


};

int main()
{
    MyContainer<int> a({1,2,3,4});
    
    for(const auto& [index,element] : a)
    {
        std::cout<<index<<"-"<<element<<std::endl;       
    }
    return 0;
}
