#include <iostream>
#include <functional>

using namespace std;

class ProxyClient{
    
    template<int T> struct type { };

    auto getFuncHandler(type<1>){
        return std::bind(&ProxyClient::sampletest1,this,std::placeholders::_1);
    }
    
    auto getFuncHandler(type<2>){
        return std::bind(&ProxyClient::sampletest2,this,std::placeholders::_1,std::placeholders::_2);
    }

    auto getFuncHandler(type<3>){
        return std::bind(&ProxyClient::sampletest3,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    }
    
    
public:
    ProxyClient(){}

    bool sampletest1(int a){
        std::cout<<"sampletest:"<<a<<std::endl;
    }

    bool sampletest2(int a,int b){
        std::cout<<"sampletest:"<<a<<b<<std::endl;
    }

    bool sampletest3(int a,int b,int c){
        std::cout<<"sampletest:"<<a<<b<<c<<std::endl;
    }

    template<int N = 1>
    auto getFuncHandler(){
        return getFuncHandler(type<N>());
    }
};

template<typename T>
class ProxyCall{
    T m_proxyObj;
public:
    ProxyCall(const T& param):m_proxyObj(param)
    {}

    template<int N,typename...Args>
    void executeCall(Args&&...args){
        auto funcHandler = m_proxyObj.template getFuncHandler<N>();
        bool res = funcHandler(std::forward<Args&&>(args)...);
    }
};

int main()
{
    ProxyClient a;
    ProxyCall<ProxyClient> exec{a};
    int x = 0;
    int y = 10;
    exec.executeCall<1>(x);
    return 0;
}
