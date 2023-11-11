#include <tuple>
#include <iostream>
#include <map>
#include <vector>

template<typename F,typename...Args>
struct MiniBinder
{
	F func;
	std::tuple<Args...> c1;
	
	MiniBinder(F f,Args...args): func(f),c1(args...)
	{}
	
	
	template<std::size_t...Is>
	decltype(auto) callFunctor(std::index_sequence<Is...>)
	{
		return (func(std::get<Is>(c1)...));	
	}
	
	decltype(auto) operator()()
	{
		return callFunctor(std::make_index_sequence<sizeof...(Args)>{});
	}
};

template<typename...T>
struct X
{
	X(const T&...values):values_(std::make_tuple(values...))
	{}
	
	std::tuple<const T&...> values_;
};

template<typename F, typename T,std::size_t...Is>
auto mini_bind_impl(F&& f1,T&& t1,std::index_sequence<Is...>)
{
	return (f1(std::get<Is>(t1)...));
}

template<typename F, typename ... Args>
auto mini_bind(F&& f1,Args...args)
{
	return mini_bind_impl(f1,std::forward_as_tuple(args...),std::make_index_sequence<sizeof...(Args)>{});
}

template<typename...Args>
int add(Args...args)
{
	return (args + ...);
}

template<typename F, typename...Args>
auto make_mini_binder(F&& f1,Args...args)
{
	return MiniBinder<F,Args...>(f1,args...);
}

struct T
{
	int x;
};

struct Tr
{
	int& xr;
	
	auto operator=(const T& other)
	{
		xr = other.x;
	}
};

int main()
{
	
	auto m_MiniBinder = make_mini_binder(add<int,int,int,int>,1,2,3,4);
	std::cout<<"---"<<m_MiniBinder()<<std::endl;
		
	std::map<int,std::tuple<int,float>> compositeContainer;
	compositeContainer.emplace(std::piecewise_construct,std::forward_as_tuple(10),std::forward_as_tuple(1,5.6f));
	std::cout<<std::get<0>(compositeContainer[10])<<std::endl;
	
	int i = 10;
	std::string x = "hi";
	auto cont = X<int,std::string>(i,x);
	std::cout<<std::get<0>(cont.values_)<<std::endl;
	
	std::tie(i) = std::make_tuple(24);
	std::cout<<i<<std::endl;
	
	std::tuple<int&>{i} = std::tuple<int>{240};
	std::cout<<i<<std::endl;
	
	Tr{i} = T{2400};			
	std::cout<<i<<std::endl;
}



