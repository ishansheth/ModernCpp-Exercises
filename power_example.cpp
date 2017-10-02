#include <iostream>

#include "square.hpp"
#include "power.hpp"
#include "f.hpp"


using namespace std;


int main (int argc, char* argv[]) 
{
 
    cout << "power(3, 2) = " << power(3, 2) << endl;
    cout << "power(3, 3) = " << power(3, 3) << endl;

    cout << "f(9) = " << f(9) << endl;

    return 0;
}

