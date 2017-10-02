#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;



int main (int argc, char* argv[]) 
{
    map<string, unsigned> markteinfuehrung;
    markteinfuehrung["Polo 6"]= 2017;
    markteinfuehrung["Polo"]= 1975;
    markteinfuehrung["Trabi"]= 1964;
    markteinfuehrung["Kaefer"]= 1938;

    cout << "Die Markteinfuehrung vom Wartburg war " << markteinfuehrung["Wartburg"] << endl;

    for (auto&& car : markteinfuehrung)
	cout << "Der " << car.first << " wurde " << car.second << " eingefuehrt.\n";
    
    const auto& mc= markteinfuehrung;
    // cout << "Die Markteinfuehrung vom Wartburg war " << mc["Wartburg"] << endl;
    auto it= mc.find("Wartburg");
    if (it == end(mc))
	cout << "Kenn ich nicht.\n";
    else
	cout << "Die Markteinfuehrung vom Wartburg war " << it->second << endl;

    if (mc.count("Robur") == 1) 
	cout << "Die Markteinfuehrung vom Robur war " << mc.at("Robur") << endl;

    unordered_map<string, unsigned> markteinfuehrung2= {{"Polo 6", 2017}, {"Robur", 1950}};
    for (auto&& car : markteinfuehrung2)
	cout << "Der " << car.first << " wurde " << car.second << " eingefuehrt.\n";

    return 0;
}

