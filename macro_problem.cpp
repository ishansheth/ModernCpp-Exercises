#include<iostream>

#define myfunc(a,b) myfunc(a,b)

int square(int a){ return a*a;}

int myfunc(int a,int b)
{
  return a+b;
}

int main()
{

  int a = myfunc(1,2);
}
