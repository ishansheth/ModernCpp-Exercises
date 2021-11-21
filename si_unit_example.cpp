#include <iostream>

template<int M, int K, int S>
struct Unit
{
    enum {m=M, kg=K, s=S};
};


using M = Unit<1,0,0>;
using Kg = Unit<0,1,0>;
using S = Unit<0,0,1>;
using MpS = Unit<1,0,-1>;
using MpS2 = Unit<1,0,-2>;

template<typename U1, typename U2>
struct Uplus
{
    using type = Unit<U1::m + U2::m, U1::kg + U2::kg, U1::s + U2::s>;
};

template<typename U1, typename U2>
using Unit_plus = typename Uplus<U1,U2>::type;


template<typename U1, typename U2>
struct Uminus
{
    using type = Unit<U1::m - U2::m, U1::kg - U2::kg, U1::s - U2::s>;
};

template<typename U1, typename U2>
using Unit_minus = typename Uminus<U1,U2>::type;

template<typename U>
struct Quantity
{
    double val;
    explicit constexpr Quantity(double d):val(d)
    {}
};

template<typename U>
bool operator==(Quantity<U> x, Quantity<U> y)
{
    return x.val==y.val;
}

template<typename U>
bool operator!=(Quantity<U> x, Quantity<U> y)
{
    return x.val!=y.val;
}

template<typename U>
Quantity<U> operator+(Quantity<U> x, Quantity<U> y)
{
    return Quantity<U>{x.val+y.val};
}

template<typename U>
Quantity<U> operator-(Quantity<U> x, Quantity<U> y)
{
    return Quantity<U>{x.val-y.val};
}

template<typename U1,typename U2>
Quantity<Unit_plus<U1,U2>> operator*(Quantity<U1> x, Quantity<U2> y)
{
    return Quantity<Unit_plus<U1,U2>>{x.val*y.val};
}

template<typename U1,typename U2>
Quantity<Unit_minus<U1,U2>> operator/(Quantity<U1> x, Quantity<U2> y)
{
    return Quantity<Unit_minus<U1,U2>>{x.val/y.val};
}


constexpr Quantity<M> operator""_m(long double d)
{
    return Quantity<M>{d};
}

constexpr Quantity<Kg> operator""_kg(long double d)
{
    return Quantity<Kg>{d};
}

constexpr Quantity<S> operator""_s(long double d)
{
    return Quantity<S>{d};
}

int main()
{
    auto distance = Quantity<M>{10.9};
    auto time = Quantity<S>{20.9};
    auto speed = distance/time;

    auto distance_2 = 10.9_m;
    auto time_2 = 20.9_s;
    auto speed_2 = distance/time;

    if(speed == 10.3_m/2.0_s)
        std::cout<<"speed is correct";

}
