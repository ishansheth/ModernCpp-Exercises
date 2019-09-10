#include <iostream>
#include <initializer_list>
#include <memory>
#include <cassert>
#include <typeinfo>
#include <vector>
#include <complex>

namespace ips{

  constexpr long fibonacci(long n){
    return n <= 2 ? 1 : fibonacci(n-1) + fibonacci(n-2);
  }

  constexpr std::size_t popcount(std::size_t x){
    int count = 0;
    for(;x != 0;++ count)
      x &= x -1;

    return count;
  }

  template<typename T> class vector_sum;

  
  template<typename T>
  class vectorf{
    unsigned int my_size;
    T* data;

  public:

    explicit vectorf(unsigned s):my_size(s),data(new T[my_size]){}

    explicit vectorf():my_size(),data(nullptr){}

    vectorf(const std::initializer_list<T>& list):my_size(list.size()),data(new T[my_size])
    {
      unsigned i = 0;
      for (T v : list) 
	data[i++]= v;       ;
    }

    ~vectorf(){
      delete[] data;
    }

    vectorf(const vectorf& that):data(new T[my_size]),my_size(that.my_size){
      for(int i = 0;i<my_size;i++)
	data[i] = that.data[i];
    }

    vectorf& operator=(const vector_sum<T>& that){
      for(int i = 0;i<my_size;i++)
	data[i] = that[i];
      return *this;
    }

    vectorf& operator=(const vectorf& that){
      my_size = that.my_size;
      for(int i = 0;i<my_size;i++)
	data[i] = that[i];
      return *this;
    }

    unsigned int size() const {
      return my_size;
    }

    T& operator[](unsigned int i) const {
      return data[i];
    }

  };


  template<typename T>
  T* begin(vectorf<T>& x){
    return x.size() ? &x[0]:nullptr;
  }

  template<typename T>
  T* end(vectorf<T>& x){
    return begin(x) + x.size();
  }

  template<typename T>
  class vector_sum{
  public:
    vector_sum(const vectorf<T>& v1,const vectorf<T>& v2): v1(v1),v2(v2){}

    friend int size(const vector_sum& x){return size(x.v1);}

    T operator[](int i) const{
      return v1[i] + v2[i];
    }
    
  private:
    const vectorf<T> &v1,&v2;
  };

  template<typename T>
  vector_sum<T> operator+(const vectorf<T>& v1,const vectorf<T>& v2){
    return {v1,v2};
  }

  template<>
  class vectorf<bool>{
    int                                    my_size;
    std::unique_ptr<unsigned char[]>       data;

  public:
    explicit vectorf(int size) : my_size(size),data(new unsigned char[(my_size+7)/8])
    {}

    vectorf():my_size(0)
    {}
    
    bool operator[](int i) const{
      return (data[i/8] >> i%8) & 1;
    }
  };


  template<typename T>
  inline T abs(const T& x){
    return x < T(0) ? -x : x;
  }
  
  template<typename T>
  inline T abs(const std::complex<T>& x){
    return sqrt(real(x)*real(x) + imag(x)*imag(x));
  }

  template<typename T, int size>
  class fsize_vec{

    using self = fsize_vec;
  public:

    using value_type = T;
    const static int my_size = size;

    fsize_vec(int s = size){assert(s == size);}

    self& operator=(const self& that){
      std::copy(that.data,that.data + size, data);
      return *this;
    }

    self operator+(const self& that){
      self sum;
      for(int i = 0;i<my_size;i++)
	sum[i] = data[i] + that[i];

      return sum;
    }

  private:
    T data[my_size];
  };

  /**
     Another benefit of knowing the size at compile time that we can store values in an array  so that our fsize_vec uses a single memeory block
     This makes creation and destruction much easier compared to dynamically allocated memory that is expensive to manange.
   **/

  /**

  template<typename T>
  struct sum_type<T>
  {
    using type = T;
  };

  template<typename T,typename... P>
  inline T sum(T t,P ...p){
    return t + sum(p...);
  }

  **/

  template <typename ...P> struct sum_type;

  template<typename T>
  struct sum_type<T>
  {
    using type = T;
  };

  template<typename T,typename ...P>
  struct sum_type<T,P...>
  {
    using type = decltype(T() + typename sum_type<P...>::type());
  };

  template<typename ...P>
  using sum_type_t = typename sum_type<P...>::type;

  template<typename T>
  inline T sum(T t){
    return t;
  }

  template<typename T, typename ...P>
  inline sum_type_t<T,P...> sum(T t, P ...p){
    return t + sum(p...);
  }

  
  template<typename T>
  struct Magnitude{
    using type = T;
  };

  template<typename T>
  struct Magnitude<std::complex<T>>{
    using type = T;
  };
  
  template<typename T>
  T inline min_magnitude(const T& x, const T& y){
    /**
       The below statement will not work if the template arguments are std::complex<>
       because there is no '<' operator for the complex number is defined in the std library
       So use auto instead of that
     //    T ax = std::abs(x),ay = std::abs(y);
       
     **/
    
    //    auto ax = std::abs(x),ay = std::abs(y);

    typename Magnitude<T>::type ax = std::abs(x),ay = std::abs(y);
    
    if( ax < ay )
      return x;
    else
      return y;
  }

  class Matrix{

    unsigned int noRow;
    unsigned int noCol;

    std::vector<std::vector<float>> data;
  public:
    using value_type = float;
    using size_type = unsigned int;

    // since the matrix will appear on the right hand side of the operator, it has to be friend method
    
    friend std::ostream& operator<<(std::ostream& os,const Matrix& m);

    Matrix(unsigned int r,unsigned int c):noRow(r),noCol(c){
      std::cout<<"row col ctor"<<std::endl;
    }

    Matrix(const Matrix& other):noRow(other.noRow),noCol(other.noCol){
      for(auto& val:other.data)
	data.push_back(val);
    }

    Matrix(std::initializer_list<std::initializer_list<float>> matData){
      std::cout<<"list ctor:"<<matData.size()<<std::endl;
      noRow = matData.size();
      for(auto& val: matData){
	data.push_back(val);
        noCol = val.size();
      }
    }
    
    value_type& operator()(size_type r,size_type c){
      return data[r][c];
    }

    void printRow(unsigned int num){
      for(unsigned int i = 0;i<data[0].size();i++){
	std::cout<<data[num][i]<<",";
      }
      std::cout<<"\n";
    }

    void printCol(unsigned int col){
      for(unsigned int i = 0;i<data.size();i++){
	std::cout<<data[i][col]<<",";
      }
      std::cout<<"\n";
    }

    const value_type& operator()(size_type r,size_type c)const{
      return data[r][c];
    }

    unsigned int getRowNum()const{
      return noRow;
    }
    
    unsigned int getColNum()const{
      return noCol;
    }

    std::vector<float> getRow(unsigned int num){
      return data[num];
    }

    std::vector<float> getCol(unsigned int num){
      std::vector<float> col;
      for(unsigned int i = 0;i<data.size();i++){	
	col.push_back(data[i][num]);
      }
      return col;
    }


  };

  template<bool Condition, typename ThenType, typename ElseType>
  struct conditional{
    using type = ThenType;
  };
  
  template<typename ThenType, typename ElseType>
  struct conditional<false,ThenType,ElseType>{
    using type = ElseType;
  };

  template<typename T>
  struct is_const{
    static const bool value = false;
  };

  template<typename T>
  struct is_const<const T>{
    static const bool value = true;
  };

  template<typename T>
  struct is_matrix : std::false_type{};

  // when T is Matrix, then below templated specialization kicks in, which is inherited from std::true_type
  template<>
  struct is_matrix<Matrix> : std::true_type{};

  template<>
  struct is_matrix<const Matrix> : std::true_type{};

  template<typename U>
  class transposed_view{
  public:
    using value_type = typename U::value_type;
    using size_type = typename U::size_type;
    
  private:
    template<bool b,class T,class F>
    using conditional_t = typename conditional<b,T,F>::type;
    
    using vref_type = conditional_t<is_const<U>::value,const value_type&,value_type&>;

    U& ref;
  public:
    transposed_view(U& A): ref(A){
      static_assert(is_matrix<U>::value,"Tarsponsed view arguments must be Matrix type");
    }

    vref_type operator()(size_type r,size_type c){
      return ref(c,r);
    }

    const value_type& operator()(size_type r,size_type c)const{
      return ref(c,r);
    }
    
  };
  
  template<typename T>
  struct is_matrix<transposed_view<T> > : is_matrix<T> 
  {};

  template<typename T>
  struct is_matrix<transposed_view<const T> > : is_matrix<const T> 
  {};

  std::ostream& operator<<(std::ostream& os,const Matrix& m){
    os<<'[';
    for(auto& val : m.data){
      for(auto& ele:val){
	os<<ele<<",";
      }
      os<<"\n";
    }
    os<<']';
    return os;
  }


  template<typename T>
  inline transposed_view<T> trans(T& A){
    return transposed_view<T>(A);
  }


  template<typename Range,typename Value>
  void print_interval(const Range& r,const Value& v,std::ostream& os = std::cout){

    using std::begin,std::end;

    auto it = std::find(begin(r),end(r),v),it2 = it;

    ++it2;
    if(it == end(r)){
      std::cout<<"value not found"<<std::endl;
      return;
    }

    auto past = std::find(it2,end(r),v);

    if(past == end(r)){
      std::cout<<"value not found"<<std::endl;
      return;
    }
    
    for(;it != past;++it)
      os<<*it<<" ";

    os<<"\n";
    
  }

}
