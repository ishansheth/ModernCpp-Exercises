#include <iostream>

using namespace std;

class vehicle
{
  public:
    virtual void all_info() const= 0;
};

class car : public vehicle
{
  public:
    car(const string& name) : name(name) {}

    virtual void all_info() const
    {  cout << "car:   My name is " << name << endl; }

    virtual ~car() {}
  protected:
    string name;
};

class truck
  : public car
{
  public:
    truck(const string& name, double weight) : car(name), weight(weight) {}

    virtual void all_info() const override
    {   cout << "truck:   My name is " << name << endl;
	cout << "I can carry " << weight << "t.\n";
    } 

  protected:
    double weight;
};



void print_all_inf(const vehicle& c) // Don't pass by value
{   c.all_info(); }

int main (int argc, char* argv[]) 
{
    truck robur("Robur LO4", 2.5);
    robur.all_info();

    car car_geslicet= robur; // Slicing
    car_geslicet.all_info();

    car& some_car= robur;
    some_car.all_info();

    car* car_ptr= &robur; 
    car_ptr->all_info();

    car* w50= new truck("W50", 4.09);
    print_all_inf(*w50);
    delete w50;

    // vehicle kein_vehicle;

    return 0;
}

