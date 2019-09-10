#include <iostream>
#include <initializer_list>
#include <exception>
#include <memory>
#include <cassert>
#include <new>
#include <typeinfo>
#include <complex>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>
#include <string>
#include "matrixlib.hxx"
#include <fstream>
#include <functional>

template<typename T>
inline T minimum(const T& t){return t;}

template<typename T,typename ...P>
typename std::common_type<T,P...>::type
minimum(const T& t,const P& ...p){
  typedef typename std::common_type<T,P...>::type res_type;
  return std::min(res_type(t),res_type(minimum(p...)));
}

class ProxyClient{
public:

  ProxyClient(){}
  
  bool serviceMethod1(int a){
    std::cout<<"in service method:"<<a<<std::endl;
  }

  bool serviceMethod2(int a,int b){
    std::cout<<"in service method:"<<a<<":"<<b<<std::endl;
  }

  bool serviceMethod3(int a,int b,int c){
    std::cout<<"in service method:"<<a<<":"<<b<<":"<<c<<std::endl;
  }

  template<int N>
  auto getClientMethod();

  template<>
  auto getClientMethod<1>(){
    return std::bind(&ProxyClient::serviceMethod1,this,std::placeholders::_1);
  }

  template<>
  auto getClientMethod<2>(){
    return std::bind(&ProxyClient::serviceMethod2,this,std::placeholders::_1,std::placeholders::_2);
  }

  template<>
  auto getClientMethod<3>(){
    return std::bind(&ProxyClient::serviceMethod2,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
  }
   
};


template<typename T>
class ProductionFunction{
  T m_proxyClient;
public:
  ProductionFunction(const T& para):m_proxyClient(para){}

  template<int N,typename...Args>
  void executeCall(Args...args){
    //    auto funchandler = m_proxyClient.getClientMethod<N>();
    
    //    funchandler(std::forward<Args>(args)...);
    //    mfunc(std::forward<Args>(args)...);
  }
};



int main(int argc, char* argv[]){

  using ips::begin,ips::end;
  
  ips::vectorf<unsigned int> func1(10);
  ips::vectorf<unsigned int> func3(func1);
  ips::vectorf<unsigned int> func2{1,2,3,34,5,6,7};

  auto s = ips::sum(-7,3.7f,9u,-42.6);
  std::cout<<"s is "<<s<<" and its type is "<< typeid(s).name()<<"\n";
  
  std::cout<<"fibonacci of 10:"<<ips::fibonacci(argc)<<std::endl;

  std::cout<<"population of 10:"<<ips::popcount(15)<<std::endl;

  double d1 = 3.4, d2 = 4.5;
  std::complex<int> c1(3),c2(5);
  std::cout<<"min ="<<ips::min_magnitude(c1,c2)<<"\n";

  ips::Matrix a{{1,2,3},{4,5,6}};
  std::cout<<"Matrix a:\n"<<a<<std::endl;
  std::cout<<"Row 1:"<<std::endl;
  a.printRow(1);
  std::cout<<"Col 2:"<<std::endl;
  a.printCol(2);
  std::cout<<"Element (1,2):"<<a(1,2)<<std::endl;
  a(1,2) = 3;
  std::cout<<"Changed Element (1,2):"<<a(1,2)<<std::endl;

  const ips::transposed_view<ips::Matrix> At(a);
  std::cout<<"Transposed Element (1,2):"<<At(1,0)<<std::endl;

  /**
     in this case, trans with non-const parameter is called.
     since a is also non-const, the non-const operator() method of transposed_view
     will be called to access the element which has a non-const return type 
   **/
  std::cout<<"Transposed Element (1,2):"<<trans(a)(1,0)<<std::endl;

  /**
     in this case, trans with non-const parameter is called.
     Here B is a const variable, which will be passed to transposed_view class and initialized
     But now, transposed_view contains a const reference variable which will call the const ref operator()
     method(of Matrix class) with return type const ref. 
     But return type of operator() method(of transposed_view) inside is non-const ref.
     so non-const ref is initialized with const ref which doesn't compile
     
     so we overload the trans method with const ref parameter and new const_transposed_view class OR 
     check at the compile time, if argument is const and put the return type of the operator() accordingly
   **/
  const ips::Matrix B(a);
  std::cout<<"copy vector changed Element (1,2):"<<trans(B)(1,0)<<std::endl;


  ips::vectorf<unsigned int> vec1{1,2,3,34,5,6,7};
  ips::vectorf<unsigned int> vec2{1,2,3,34,5,6,7};

  std::cout<<"From range based loop"<<std::endl;
  for(auto& i : vec1){
    std::cout<<i<<std::endl;
  }
  ips::vectorf<unsigned int> vec3(7);

  vec3 = vec1 + vec2;

  ips::vectorf<unsigned int> vec4 = vec3;


  std::list<int> seq = {3,4,7,9,2,5,7,8};
  ips::print_interval(seq,7);


  std::string text = "Let me split this into words";

  std::stringstream iss(text);
  std::cout<<iss.str();

  std::vector<std::string> result(std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>());

  for(auto i : result)
    std::cout<<i<<std::endl;


  std::ifstream ifs;
  ifs.open("/home/ishan/index.jpeg",std::ios::in);
  
  std::vector<char> imagedata(std::istream_iterator<char>{ifs},std::istream_iterator<char>());

  std::cout<<"vec size:"<<imagedata.size()<<std::endl;

  std::cout<<"size of unsigned int:"<<sizeof(unsigned int)<<std::endl;
  std::cout<<"size of char:"<<sizeof(char)<<std::endl;
  std::cout<<"size of int:"<<sizeof(int)<<std::endl;

  ProxyClient prClient;

  auto funchandle = prClient.getClientMethod<1>();
  //  ProductionFunction<ProxyClient> prodFunc{prClient};
  //  int a1 = 5,a2 = 10;
  //  prodFunc.executeCall<1>(a1);
  
  return 0;
}
