#include <iostream>

using namespace std;

class car 
{
    virtual void init() const { cout << "init car.\n"; }
  public:
    car(const string& name) : name(name) { init(); }

    virtual void all_info() const
    {  my_info(); }

    void my_info() const
    {  cout << "car:   My name is " << name << endl; }

    virtual ~car() {}
  protected:
    string name;
};

class truck : public virtual car
{
    virtual void init() const override { cout << "init truck.\n"; }
  public:
    truck(const string& name, double weight) : car(name+"[truck]"), weight(weight) {}

    virtual void all_info() const override
    {   car::all_info();
	my_info();
    } 
    void my_info() const
    {
	cout << "I can carry " << weight << "t.\n";
    } 

  protected:
    truck(double weight) : car(""), weight(weight) {}
    double weight;
}; 

class vw : public virtual car
{
    virtual void init() const override  { cout << "init vw.\n"; }
  public:
    vw(const string& name, double feinstaub) : car(name+"[vw]"), feinstaub(feinstaub) {}

    virtual void all_info() const override
    {   cout << "WV:   My name is " << name << endl;
	my_info();
    } 

    void my_info() const
    { 
	cout << "I pollute " << feinstaub << "mug.\n";
    }

  protected:
    vw(double feinstaub) : car(""), feinstaub(feinstaub) {}
    double feinstaub;
};

class vw_nutzfahrzeuge : public vw, public truck
{
    virtual void init() const override { cout << "init vw_nutzfahrzeuge.\n"; }
  public:
    vw_nutzfahrzeuge(const string& name, double feinstaub, double weight)
      : car(name), vw(feinstaub), truck(weight) {}

    virtual void all_info() const override
    {
	vw::all_info(); truck::my_info();
    }
};

void print_all_inf(const car& c) // Don't pass by value
{   c.all_info(); }

int main (int argc, char* argv[]) 
{
    vw_nutzfahrzeuge crafter("Crafter", 0.000000001e20, 3.5);
    crafter.all_info();

    cout << endl << endl;

    static_cast<car&>(static_cast<vw&>(crafter)).my_info();
    static_cast<car&>(static_cast<truck&>(crafter)).my_info();

    static_cast<car&>(crafter).my_info();
    
    return 0;
}

