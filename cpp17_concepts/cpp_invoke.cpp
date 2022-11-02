#include <iostream>
#include <functional>

int do_something(int i)
{
    return i+5;
}

int do_something_2(int i,int j)
{
    return i+j;
}


struct Animal
{
    public:
    void run(int n)
    {
        std::cout<<"running "<<n<<" kilometers\n";
    }

};


template<typename F,typename...Args>
auto  callFunctor(F&& f,Args&&...args)
{
    return std::invoke(f,std::forward<Args>(args)...);
}

int main()
{
    Animal a;
    std::cout<<std::invoke(&do_something,10)<<std::endl;
    std::invoke(&Animal::run,a,10);

    auto fp = &Animal::run;
    (a.*fp)(10);

    std::cout<<callFunctor(&do_something,2)<<std::endl;
    std::cout<<callFunctor(&do_something_2,2,2)<<std::endl;

}