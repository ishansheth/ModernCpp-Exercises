#include <iostream>
#include <typeinfo>
#include <memory>
#include <type_traits>

using namespace std;

namespace preh {

    template <typename T>
    struct is_pointer
    {
	static const bool value= false;
    };

    template <typename T>
    struct is_pointer<std::unique_ptr<T>>
      : true_type {};

    template <typename T>
    struct is_pointer<T*>
    {
	static const bool value= true;
    };

    template <typename T>
    struct is_pointer<T const>
      : is_pointer<T> {};

#if 0
    {
	static const bool value= is_pointer<T>::value;
    };
#endif
    
    template <typename T>
    void print_is_pointer()
    {
	cout << typeid(T).name() << " ist " << (is_pointer<T>::value ? "ein" : "kein") << " Zeiger.\n";	    
    }

    struct dings {};

    template <typename T>
    void only_for_pointer(const T& p)
    {
	static_assert(is_pointer<T>::value, "Eh Aldaa, du bist kein Pointer, du kommst hier nicht rein!");
	cout << "In only_for_pointer.\n";
    }

    template <typename T>
    struct in_si
      : std::integral_constant<bool, (sizeof(T) > 4)> {};

    template <typename T>
    void navigate_dispatch(const T& x, true_type)
    {
	// Ganz viel zu tun ...
	cout << "Navigate in SI.\n";
    }

    template <typename T>
    void navigate_dispatch(const T& x, false_type)
    {
	// Ganz viel zu tun ...
	cout << "Navigate in imperial units.\n";
    }

    template <typename T>
    void navigate(const T& x)
    {
	navigate_dispatch(x, in_si<T>());
    }
}


int main (int argc, char* argv[]) 
{
    using namespace preh;

    print_is_pointer<int>();
    print_is_pointer<int*>();
    print_is_pointer<float*>();
    print_is_pointer<const float*>();
    print_is_pointer<float* const>();
    print_is_pointer<dings*>();
    print_is_pointer<unique_ptr<dings>>();

    int* p;
    only_for_pointer(p);
    // only_for_pointer(3);

    navigate(3.9);
    navigate('f');


    return 0;
}

