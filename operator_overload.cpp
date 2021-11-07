#include <iostream>
#include <cstdlib>
#include <cstring>

namespace ips
{
  
  class complex
  {
    double re,im;

  public:

    complex():re(0),im(0){}
  
    complex(double r, double i):re(r),im(i){}

    complex& operator+=(complex& that)
    {
      re += that.re;
      im += that.im;
      return *this;
    }

    complex& operator-=(complex& that)
    {
      re -= that.re;
      im -= that.im;
      return *this;
    }

    complex& operator-()
    {
      std::cout<<"unary operator"<<std::endl;
      re = -re;
      im = -im;
      return *this;
    }
    
    // absolute value of the complex number
    operator double()
    {
      std::cout<<"operator double"<<std::endl;
      return (re*re + im*im);
    }
    
    double real()const {return re;}
    
    double imag()const {return im;}

    void real(double r){re = r;}

    void imag(double i){im = i;}
    
    friend std::ostream& operator<<(std::ostream& os, complex& a);
    
    //  complex operator*(complex);
  };


  std::ostream& operator<<(std::ostream& os, complex& a)
  {
    if(a.im > 0)
      os<<a.re<<"+"<<a.im<<"i";
    else
      os<<a.re<<a.im<<"i";    
    return os;
  }

  /*String class implementation from C++ Stroustrup book*/

  char* expand(const char* ptr,int n)
  {
    char* p = new char[n];
    strcpy(p,ptr);
    return p;
  }

  class String
  {
    static const int short_max = 15;
    int sz;//number of characters
    char* ptr;
    union{
      int space;//unused allocated space
      char ch[short_max+1];//leave space terminating 0
    };

    void check(int n) const
    {
      if(n < 0 || sz <= n)
	throw std::out_of_range("String::at()");
    }
    
  public:
    String():sz{0},ptr{ch}
    {
      ch[0] = 0;
    }

    String(const char* p):sz{strlen(p)},ptr{(sz<=short_max)?ch:new char[sz+1]},space{0}
    {
      strcpy(ptr,p);
    }

    String(const String& x)
    {
      copy_from(x);
    }

    String(String&& x)
    {
      move_from(x);
    }

    String& operator=(const String& x)
    {
      if(this==&x)//deal with self-assignment
	return *this;

      char* p = (short_max<sz)?ptr:0;

      copy_from(x);
      delete[] p;
      return *this;
    }

    String& operator=(String&& x)
    {
      if(this==&x)//deal with self-assignment
	return *this;

      if(short_max<sz)
	delete[] ptr;

      move_from(x);
      return *this;      
    }

    String& operator+=(char c)
    {
      if(sz==short_max)
	{
	  int n = sz + sz + 2;
	  ptr = expand(ptr,n);
	  space = n-sz-2;
	}
      else if(short_max < sz)
	{
	  if(space == 0)
	    {
	      int n = sz + sz + 2;
	      char* p = expand(ptr,n);
	      delete[] ptr;
	      ptr = p;
	      space = n - sz - 2;
	    }
	  else
	    {
	      --space;
	    }
	}
      ptr[sz] = c;
      ptr[++sz] = 0;
      return *this;      
    }
    
    void copy_from(const String& x)
    {
      if(x.sz <= short_max)
	{
	  memcpy(this,&x,sizeof(x));
	  ptr = ch;
	}
      else
	{
	  ptr = expand(x.ptr,x.sz+1);
	  sz = x.sz;
	  space = 0;
	}
    }


    void move_from(String& x)
    {
      if(x.sz <= short_max)
	{
	  memcpy(this,&x,sizeof(x));
	  ptr = ch;
	}
      else
	{
	  ptr = x.ptr;
	  sz = x.sz;
	  space = x.space;
	  x.ptr = x.ch;
	  x.sz = 0;
	  x.ch[0]=0;
	}
    }

    char& operator[](int n) {return ptr[n];}
    char operator[](int n) const {return ptr[n];}

    char& at(int n){check(n); return ptr[n];}

    char at(int n) const {check(n); return ptr[n];}

    char* c_str(){return ptr;}
    const char* c_str()const{return ptr;}

    int size()const{return sz;}
    int capacity()
    {
      return (sz<=short_max) ? short_max : sz + short_max;
    }
  };

  std::ostream& operator<<(std::ostream& os, const String& s)
  {
    return os<<s.c_str();
  }

  bool operator==(const String& a, const String& b)
  {
    if(a.size() != b.size())
      return false;
    for(int i = 0;i !=a.size();i++)
      if(a[i] != b[i])
	return false;

    return true;
  }

  bool operator!=(const String& a, const String& b)
  {
    return !(a==b);
  }

  char* begin(String& x)
  {
    return x.c_str();
  }

  char* end(String& x)
  {
    return x.c_str()+x.size();
  }

  const char* begin(const String& x)
  {
    return x.c_str();
  }

  const char* end(const String& x)
  {
    return x.c_str()+x.size();
  }

  String& operator+=(String& a, const String& b)
  {
    for(auto x:b)
      a += x;

    return a;
  }


  template<typename T,typename A = allocator<T>>
  class vector
  {
    T* elem; // start of allocation
    T* space;  // end of element sequence
    T* last;  //end of allocated space
    A alloc;

  public:

    using size_type = typename A::size_type;

    explicit vector(size_type n, const T& val = T(), const A& = A()):alloc(a)
    {
      elem = alloc.allocate(n);
      T* p;
      try
	{
	  auto end = elem + n;
	  for(p = elem ; p!= end; ++p)
	    alloc.construct(p,val);

	  last = space = p;	  
	}
      catch(...)
	{
	  for(auto q = elem;q!=p;q++)
	    alloc.destroy(q);
	  
	  alloc.deallocate(elem,n);
	  throw;
	}
    }

    
  };

}

ips::complex operator+(const ips::complex& a1,const ips::complex& a2)
{
  ips::complex r;
  r.real(a1.real()+a2.real());
  r.imag(a1.imag()+a2.imag());
  return r;
}

ips::complex operator+(double i,ips::complex& j)
{
  return (ips::complex{i,0}+j);
}

ips::complex& operator-(ips::complex& a1,ips::complex& a2)
{
  ips::complex r;  
  r.real(a1.real()-a2.real());
  r.imag(a1.imag()-a2.imag());
  return r;
}

long double  operator""_deg(long double deg)
{
  return (deg * 3.1442342342342L)/180;
}

ips::complex operator""_i(long double i)
{
  return ips::complex{0,i};
}


int main()
{
  ips::complex a(1,-2);
  ips::complex b(3,4);

  ips::complex c;
  
  c = a+b;
  std::cout<<"a:"<<a<<std::endl;
  std::cout<<"c:"<<c<<std::endl;

  std::cout<<c<<std::endl;
  std::cout<<-c<<std::endl;

  std::cout<<double(c)<<std::endl;


  auto c1 = 1+2.0i;
  std::cout<<"c1:"<<c1<<std::endl;
  double x = 90.0_deg;

  std::cout<<"a:"<<a<<std::endl;
  
  ips::complex c2 = 3.0 + a;
  std::cout<<c2<<std::endl;
}
