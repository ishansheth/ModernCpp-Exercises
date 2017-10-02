#include <iostream>

using namespace std;

using tagegdsaaga= int*;


namespace preh {

    void f(unsigned u)
    {
	cout << "f(unsigned)\n";
    }

    void f(unsigned* p)
    {
	cout << "f(unsigned*)\n";
    }
}


int main (int argc, char* argv[]) 
{
    using namespace preh;

    // f(0); // mehrdeutig
    // f(NULL);

    f(0u); 
    f((unsigned*)(0));
    f(nullptr);

    tagegdsaaga p= nullptr;
    if (p == nullptr)
	cout << "Dacht ich mir.\n";

    return 0;
}

