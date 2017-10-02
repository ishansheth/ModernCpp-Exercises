#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

namespace preh {

    template <typename T>
    T max(T a, T b)
    {
	return a < b ? b : a;
	// return a < b ? b.value : a.value; // Only a problem when T has no value member
    }
}


int main (int argc, char* argv[]) 
{
    cout << "max(3, 6) = " << preh::max(3, 6) << endl;
    cout << "max(3., 6.) = " << preh::max(3., 6.) << endl;

    // cout << "max(3, 6.) = " << preh::max(3, 6.) << endl;
    cout << "max(3, 6.) = " << preh::max(double(3), 6.) << endl; // double   
    cout << "max(3, 6.) = " << preh::max<float>(3, 6.) << endl; // float

    // cout << "max(zwei, sechs) = " << preh::max("zwei"s, "sechs"s) << endl;
    // cout << "max(zwei, sechs) = " << preh::max(string("zwei"), string("sechs")) << endl;
    
    vector<int> v= {3, 2, 7, 9};
    sort(begin(v), end(v));
    cout << "v ist "; copy(begin(v), end(v), ostream_iterator<int>(cout, ",")); cout << endl;

    // const vector<int> w(v);
    // sort(begin(w), end(w));

    vector<string> vs= {{"zwei"s, "sechs"s, "eins"s}};
    sort(begin(vs), end(vs));
    cout << "vs ist "; copy(begin(vs), end(vs), ostream_iterator<string>(cout, ",")); cout << endl;

    
    return 0;
}

