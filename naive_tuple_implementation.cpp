#include <iostream>

/*===========================================================================================================*/
namespace ips
{
  struct null_arg {};

  template<typename T1,typename T2,typename T3,typename T4> struct Tuple;
  
  template<>
  struct Tuple<null_arg,null_arg,null_arg,null_arg>
  {
    Tuple(){}
  };

  template<typename T1=null_arg,typename T2=null_arg,typename T3=null_arg,typename T4=null_arg>
  struct Tuple:Tuple<T2,T3,T4>
  {
    T1 x;

    using Base = Tuple<T2,T3,T4>;
    Base* base()
    {
      return static_cast<Base*>(this);
    }
    
    const Base* base() const
    {
      return static_cast<const Base*>(this);
    }

    
    Tuple(const T1& t1,const T2& t2,const T3& t3,const T4& t4):Base{t2,t3,t4},x{t1}
    {}
  };


  template<typename T1>
  struct Tuple<T1>:Tuple<>
  {
    T1 x;

    using Base = Tuple<>;
    Base* base()
    {
      return static_cast<Base*>(this);
    }
    const Base* base() const
    {
      return static_cast<const Base*>(this);
    }

    Tuple(const T1& t1):Base{},x{t1}
    {}
  };

  template<typename T1,typename T2>
  struct Tuple<T1,T2>:Tuple<T2>
  {
    T1 x;
    using Base = Tuple<T2>;    
    Base* base()
    {
      return static_cast<Base*>(this);
    }
    const Base* base() const
    {
      return static_cast<const Base*>(this);
    }

    Tuple(const T1& t1,const T2& t2):Base{t2},x{t1}
    {}
  };


  template<typename T1,typename T2,typename T3>
  struct Tuple<T1,T2,T3>:Tuple<T2,T3>
  {
    T1 x;
    using Base = Tuple<T2,T3>;
    Base* base()
    {
      return static_cast<Base*>(this);
    }
    const Base* base() const
    {
      return static_cast<const Base*>(this);
    }

    Tuple(const T1& t1,const T2& t2,const T3& t3):Base{t2,t3},x{t1}
    {}
  };



  template<typename T1,typename T2,typename T3,typename T4>
  void print_elements(std::ostream& os, const Tuple<T1,T2,T3,T4>& t)
  {
    os << t.x << ",";
    print_elements(os,*t.base());
  }

  template<typename T1,typename T2,typename T3>
  void print_elements(std::ostream& os, const Tuple<T1,T2,T3>& t)
  {
    os << t.x << ",";
    print_elements(os,*t.base());
  }

  template<typename T1,typename T2>
  void print_elements(std::ostream& os, const Tuple<T1,T2>& t)
  {
    os << t.x << ",";
    print_elements(os,*t.base());
  }

  template<typename T1>
  void print_elements(std::ostream& os, const Tuple<T1>& t)
  {
    os << t.x ;
  }

  template<>
  void print_elements(std::ostream& os, const Tuple<>& t)
  {
    os << " ";
  }

  template<typename T1,typename T2,typename T3,typename T4>
  std::ostream& operator<<(std::ostream& os,const Tuple<T1,T2,T3,T4>& t)
  {
    os << "{";
    print_elements(os,t);
    os << "}";
    return os;
  }

  template<typename Ret,int N>
  struct getNth
  {
    template<typename T>
    static Ret& get(T& t)
    {
      return getNth<Ret,N-1>::get(*t.base());
    }
  };

  // template partial specilization
  template<typename Ret>
  struct getNth<Ret,0>
  {
    template<typename T>
    static Ret& get(T& t)
    {
      return t.x;
    }
  };

  template<int i, typename T1=null_arg,typename T2=null_arg,typename T3=null_arg,typename T4=null_arg>
  struct select;

  template<typename T1,typename T2,typename T3,typename T4>
  struct select<0,T1,T2,T3,T4>
  {
    using type = T1;
  };

  template<typename T1,typename T2,typename T3,typename T4>
  struct select<1,T1,T2,T3,T4>
  {
    using type = T2;
  };

  template<typename T1,typename T2,typename T3,typename T4>
  struct select<2,T1,T2,T3,T4>
  {
    using type = T3;
  };

  template<typename T1,typename T2,typename T3,typename T4>
  struct select<3,T1,T2,T3,T4>
  {
    using type = T4;
  };
  
  template<int i, typename T1=null_arg,typename T2=null_arg,typename T3=null_arg,typename T4=null_arg>
  using Select = struct select<i,T1,T2,T3,T4>::type;


  template<int N,typename T1=null_arg,typename T2=null_arg,typename T3=null_arg,typename T4=null_arg>
  typename select<N,T1,T2,T3,T4>::type& get(Tuple<T1,T2,T3,T4>& t)
  {
    return getNth<Select<N,T1,T2,T3,T4>,N>::get(t);
  }

}

int main()
{
  ips::Tuple<double,char,int,std::string> x{1.1,'a',10,"ishansheth"};
  std::cout<<ips::get<0>(x);

}
