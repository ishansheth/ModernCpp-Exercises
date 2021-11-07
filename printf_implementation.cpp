#include <iostream>

namespace ips
{

  void printf(const char* s)
  {
    if(s == nullptr)
      return;

    while(*s)
      {
	if(*s == '%' && *++s!='%') // check no '%d' kind of pattern is there in a string with no format specification
	  {
	    throw std::runtime_error("invalid format: missing argument");
	  }
	std::cout<< *s++;
      }
  }

  template<typename T,typename...Args>
  void printf(const char* s,T value,Args... args)
  {
    while(s)
      {
	if(*s=='%') // check if there is '%d, %s' kind of pattern in there in a format-string and then print 'value' of that variable
	  {
	    switch(*++s)
	      {
	      case '%':
		break;
		
/*	      case 's':
		if(!Is_C_style_string<T>() && !Is_string<T>())
		  throw std::runtime_error("Bad printf() format");
		break;
		
	      case 'd':
		if(!Is_integral<T>())
		  throw std::runtime_error("Bad printf() format");
		break;

	      case 'g':
		if(!Is_floating_point<T>())
		  throw std::runtime_error("Bad printf() format");
		  break;*/
	      }
	    std::cout<<value;  // here we are not checking the type of a 'value'
	    return printf(++s,args...);	  
	  }
	std::cout<<*s++;
      }
    throw std::runtime_error("extra argument provided to printf");
  }

  template<typename F,typename...T>
  void call(F&& f,T&&...t)
  {
    f(std::forward<T>(t)...);
  }

  void g0()
  {
    std::cout<<"g0"<<std::endl;
  }

  template<typename T>
  void g1(const T& t)
  {
    std::cout<<"g1:"<<t<<std::endl;
  }

  void g1d(double d)
  {
    std::cout<<"g1d:"<<d<<std::endl;
  }

  template<typename T1,typename T2>
  void g2(const T1& t1,const T2& t2)
  {
    std::cout<<"g2()"<<t1<<" "<<t2<<std::endl;
  }

  void test()
  {
    call(g0);
    call(g1d,10);
  }
  
}


int main()
{
  const char* a = "ishan sheth";
  ips::printf("%s",a);

  ips::test();
  
}
