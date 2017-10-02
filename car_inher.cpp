#include <iostream>

class car
{
	public:
		car(const std::string& name) : name(name)
		{}
		
	void all_info() const
	{
		std::cout<< "car name:"<<name<<std::endl;
	}
	
	protected:
		std::string name;
};

class truck : public car
{
	public:
		truck(const std::String& name, double weight): car(name), weight(weight)
		{}
		
		void all_info()
		{
			std::cout<< "truck : My name is " << name <<std::endl;
			std::cout<< "I can carry "<< weight<< std::endl;
		}
		
	protected:
		double weight;
};

int main(int argc, char* arhv[])
{
	truck robur("Robur L04",2.5);
	robur.all_info();
	
	
}