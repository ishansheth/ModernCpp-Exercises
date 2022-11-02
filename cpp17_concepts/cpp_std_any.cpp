/*
    An example to learn the std::any which is added in c++17
*/
#include <iostream>
#include <any>
#include <vector>
#include <type_traits>

struct Animal
{
    Animal() = default;
    Animal(const Animal& other) = delete;
    // if you don't define it as default, std::is_move_constructible fails
    // because, since you did not define it, it was not given to you implicitely
    // and since it does not exist, the class is not move constructible
    Animal(Animal&& other) = default;
};

int main()
{
    std::vector<std::any> container{1,2.f,3.4,"ishansheth"};
    std::cout<<std::any_cast<int>(container[0])<<"\n";

    static_assert(std::is_nothrow_move_constructible<Animal>::value);

    try
    {
        std::cout<<std::any_cast<float>(container[0])<<"\n";
    }
    catch(const std::bad_any_cast& e)
    {
        // when casting fails, it throws exception
        // to inspect thee type, type() method of std::any can be used
        std::cout<<"Any cast failed for the element 0 of container, type is "<<container[0].type().name()<<std::endl;
    }

    // the ibject that can be used with std::any must be copy constructible
    // the below line fails to compile
    // std::vector<std::any> another_cont{1,2.f,Animal()};

    int* value = std::any_cast<int>(&container[0]);
    *value = 10;
    std::cout<<std::any_cast<int>(container[0])<<"\n";

}