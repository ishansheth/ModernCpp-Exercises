#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <cassert>

template<typename, typename>
struct forNArgsImpl;

template<std::size_t TArity,typename TF, typename... Ts>
void forNArgs(TF&& mFn,Ts&&... mXs)
{
    constexpr auto numberOfArgs(sizeof...(Ts));
    static_assert(numberOfArgs % TArity == 0, "Invalid number of Args");

    forNArgsImpl<std::make_index_sequence<numberOfArgs / TArity>,
				std::make_index_sequence<TArity>>::exec(mFn,
						std::forward_as_tuple(std::forward<Ts>(mXs)...));
}


template<std::size_t...TNCalls,std::size_t... TNArity>
struct forNArgsImpl< std::index_sequence<TNCalls...>,
					std::index_sequence<TNArity...> >
{
    template<typename TF,typename...Ts>
    static void exec(TF&& mFn, const std::tuple<Ts...>& mXs)
    {
        constexpr auto arity(sizeof...(TNArity));
        using swallow = bool[];

        (void)swallow{(execN<TNCalls * arity>(mFn,mXs),true)...};
    }

    template<std::size_t TNBase,typename TF, typename...Ts>
    static void execN(TF&& mFn,const std::tuple<Ts...>& mXs)
    {
        mFn(std::get<TNBase + TNArity>(mXs)...);
    }
};

template<typename... TArgs>
auto make_unordered_map(TArgs&&... mArgs);

template<typename TSeq,typename... Ts>
struct CommonKVHelper;

template<std::size_t... TIs, typename...Ts>
struct CommonKVHelper<std::index_sequence<TIs...>, Ts...>
{
	static_assert(sizeof...(Ts)%2 == 0, "");

	template<std::size_t TI>
	using TypeAt = std::tuple_element_t<TI,std::tuple<Ts...>>;

	using KeyType = std::common_type_t<TypeAt<TIs*2>...>;
	using ValueType = std::common_type_t<TypeAt<TIs*2 +1>...>;
};

template<typename... Ts>
using HelperFor = CommonKVHelper<std::make_index_sequence<sizeof...(Ts)/2>,Ts...>;

template<typename...Ts>
using CommonKeyType = typename HelperFor<Ts...>::KeyType;

template<typename...Ts>
using CommonValueType = typename HelperFor<Ts...>::ValueType;


static_assert(std::is_same<CommonKeyType<std::string,int>,std::string>(),"");

static_assert(std::is_same<CommonValueType<std::string,int>,int>(),"");

template<typename... TArgs>
auto make_unordered_map(TArgs&&... mArgs)
{
	using KeyType = CommonKeyType<TArgs...>;
	using ValueType = CommonValueType<TArgs...>;

	std::unordered_map<KeyType,ValueType> result;
	result.reserve(sizeof...(TArgs)/2);

	forNArgs<2>(
			[&result](auto&& k,auto&& v)
			{
				result.emplace(std::forward<decltype(k)>(k),std::forward<decltype(v)>(v));
			},
			std::forward<TArgs>(mArgs)...
			);
	return result;
};

template<typename F, typename...T>
void forArgs(F&& func,T&&...args)
{
	(void)std::initializer_list<int>{(func(std::forward<T>(args)),0)...};
}

template<typename...T>
auto make_vector(T&&...args)
{
	using VectorType = std::common_type_t<T...>;
	std::vector<VectorType> result;

	result.reserve(sizeof...(T));

	forArgs([&result](auto&& k){result.emplace_back(std::forward<decltype(k)>(k));},std::forward<T>(args)...);

	return result;

}


template<typename F,typename T,std::size_t...Is>
void forTupleImpl(F f,T&& t, std::index_sequence<Is...>)
{
	forArgs(f,std::get<Is>(std::forward<T>(t))...);
}


template<typename F,typename T>
void forTuple(F&& func,T t )
{
	std::cout<<"tuple size:";
	std::cout<<std::tuple_size<std::remove_reference_t<decltype(t)>>::value<<std::endl;

	using seq = std::make_index_sequence<std::tuple_size<std::remove_reference_t<decltype(t)>>::value>;

	forTupleImpl(std::forward<F>(func),std::forward<T>(t),seq{});
}


int main()
{
	using namespace std::literals;

	auto m = make_unordered_map("zero"s,0,"one"s,1,"two"s,2.f);

	static_assert(std::is_same<decltype(m),std::unordered_map<std::string,float>>(),"");

	std::cout<<m["zero"]<<" "<<m["one"]<<" "<<m["two"]<<std::endl;

	auto vec(make_vector(1,2,3,4,5));

	std::cout<<"size of vector from make vector:"<<vec.size()<<std::endl;
	forTuple([](auto&& k){std::cout<<k;},std::make_tuple(1,2,3,4,"himalaya"));
}

