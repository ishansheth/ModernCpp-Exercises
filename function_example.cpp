#include <iostream>
#include <cmath>
// Besser als math.h

using namespace std;

// Als Wert uebergeben -> kopiert -> Quatsch
// void increment(int i)
// {
//     ++i;
// }

// Als Referenz uebergeben
void increment(int& i)
{    ++i; }

// void increment(const int& i)
// {    
//     cout << "Alter, das ist eine increment-Funktion! Was soll der Quatsch?\n"; 
// }


// double norm(const vector& v) { ... } // fuer grosse Daten

int square(int i)
{     return i * i;   }

void dont_change(const int& i)
{   
    cout << "dont_change: i ist " << i << endl; 
    // i= 17;
    // increment(i);
    cout << "   das Quadrat ist " << square(i) << endl;
}

inline double root(double x, int degree= 2)
{
    return pow(x, 1.0 / degree);
}

int main (int argc, char* argv[]) 
{
    // printf("Das ist eine %s.\n", 32346236);
    cout << "Das ist eine " << 3 << ".\n";

    int i= 3;
    increment(i);
    cout << "i ist " << i << ".\n";
    cout << "Das Quadrat von i ist " << square(i) << ".\n";
    dont_change(i);

    // increment(9);
    dont_change(9);
    // cout << "Das Quadrat von 3.5 ist " << square(3.5) << ".\n";

    cout << "Root of 7 = " << root(7.0) << ".\n";
    cout << "Third root of 7 = " << root(7.0, 3) << ".\n";

    return 0;
}

