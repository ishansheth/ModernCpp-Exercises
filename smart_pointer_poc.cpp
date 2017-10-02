#include <iostream>
#include <memory>

int* getValue(int j)
{
	int* i = new int(50);
	*i = *i + j;
	return i;
}

int main(int argc, char* argv[])
{
	std::unique_ptr<int> intPtr(new int);
	*intPtr = 5;
	std::cout<<*intPtr<<std::endl;
	int* res = getValue(10);
	std::cout<<*res<<std::endl;
	return 0;
}