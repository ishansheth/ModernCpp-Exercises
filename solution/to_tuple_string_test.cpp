#include <iostream>
#include <cassert>
#include <sstream>

using namespace std;

namespace preh {

    template <typename T>
    string to_string(const T& x)
    {
	std::stringstream ss;
	ss << x;
	return ss.str();
    }

    template <typename T>
    string to_tuple_string_aux(const T& x)
    {
	return to_string(x);
    } 

    template <typename T, typename ...P>
    string to_tuple_string_aux(const T& x, const P& ...p) 
    {
	return to_string(x) + ", " + to_tuple_string_aux(p...);
    }
 
    template <typename ...P>
    string to_tuple_string(const P& ...p)
    {
	return "(" + to_tuple_string_aux(p...) + ")";
    }
}


int main (int argc, char* argv[]) 
{
    assert(preh::to_tuple_string(3, 3.7, "huhu") == "(3, 3.7, huhu)");

    return 0;
}

