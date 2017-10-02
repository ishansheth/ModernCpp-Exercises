#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

namespace preh {

    // int& fr_stale() {
    // 	int i= 9;
    // 	return i; // Stale reference!!!!
    // } 
 
    // int* fp_stale() {
    // 	int i= 9;
    // 	return &i; // Stale reference!!!! 
    // } 


}


int main (int argc, char* argv[]) 
{
    using namespace preh;

    // Rubbish in memory
    vector<int>* vp= (vector<int>*) malloc(sizeof(vector<int>));

    // default constructor called
    vector<int>* vp2= new vector<int>;

    // just allocated
    int* ip= new int;

    // initialized with 3
    int* ip3= new int(3);

    // 3 ints
    int* ipa3= new int[3];

    
    free(vp);
    delete vp2;
    delete ip;
    delete ip3;
    delete[] ipa3;

    int i= 7;
    int& j= i;
    for (int k= 0; k < 3; ++k) {
	int& ipa3k= ipa3[k];
	ipa3k= k;
    }
 
    return 0;
}

