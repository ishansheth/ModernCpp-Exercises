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
}


int main (int argc, char* argv[]) 
{
    using namespace preh;

    assert(preh::to_string(3) == "3");
    assert(preh::to_string(3.7) == "3.7");
    assert(preh::to_string("huhu") == "huhu");

    return 0;
}

