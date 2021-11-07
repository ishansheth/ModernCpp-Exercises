/*
this example is from the book C++ Programming by Bjarne Stroustrup

T-> is a value type of the matrix e.g. int, float, complex
N-> number of dimensions in a matrix
*/

#include <iostream>
#include <fstream>

/*
namespace ips
{

  struct slice
  {
    slice():start(-1),length(-1),stride(1){}
    explicit slice(std::size_t s):start(s),length(-1),stride(1){}

    slice(std::size_t s,std::size_t l,std::size_t n=1):start(s),length(l),stride(n)
    {}

    std::size_t operator()(std::size_t i) const{return start+i*stride;}

    static slice all;

    std::size_t start;
    std::size_t length;
    std::size_t stride;
    
  };
  
  template<std::size_t N>
  struct Matrix_slice
  {
    Matrix_slice() = default;

    Matrix_slice(std::size_t offset,std::initializer_list<std::size_t> exts);
    Matrix_slice(std::size_t offset,std::initializer_list<std::size_t> exts,std::initializer_list<std::size_t> strs);

    template<typename...Dims>
    Matrix_slice(Dims... dims);

    template<typename...Dims,typename = std::enable_if<All(Convertible<Dims,std::size_t>()...)>>
    std::size_t operator()(Dims...dims) const
    {
      static_assert(sizeof...(Dims)==N,"Matrix_slice<N>::operator() dimensions mismatch");
      
      std::size_t args[N]{std::size_t(dims)...}

      return start+inner_product(args,args+N,strides.begin(),std::size_t{0});
    }

    std::size_t size;
    std::size_t start;
    std::array<std::size_t,N> extents;
    std::array<std::size_t,N> strides;
  };

  
  template<typename T,std::size_t N>
  class Matrix
  {
  public:
    static constexpr std::size_t order = N;
    using value_type = T;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    Matrix() = default;
    Matrix(const Matrix&) = default;
    Matrix(Matrix&&) = default;

    Matrix& operator=(Matrix&&) = default;
    Matrix& operator=(const Matrix&) = default;
    ~Matrix() = default;

    template<typename U>
    Matrix(const Matrix_ref<U,N>& x):desc{x.desc},elems{x.begin(),x.end()}
    {
      static_assert(Convertible<U,T>(),"Matrix constructor, incompatible element types");
    }
    
    template<typename U>
    Matrix& operator=(const Matrix_ref<U,N>& x)
    {
      static_assert(Convertible<U,T>(),"Matrix constructor, incompatible element types");
      desc = x.desc;
      elems.assign(x.begin(),x.end());
      return *this;
    }

    template<typename...Exts>
    explicit Matrix(Exts... exts):desc(exts...),elems(desc.size)
    {}

    Matrix(Matrix_initializer<T,N> init)
    {
      desc.extents = Matrix_impl::derive_extents(init);
      Matrix_impl::compute_strides(desc);
      elems.reserve(desc.size);
      Matrix_impl::insert_flat(init,elems);
      assert(elems.size() == desc.size);
    }
    
    Matrix& operator=(Matrix_initializer<T,N>);

    template<typename U>
    Matrix(std::initializer_list<U>) = delete;

    template<typename U>
    Matrix& operator=(std::initializer_list<U>) = delete;

    std::size_t extent(std::size_t n) const { return desc.extents[n]; }

    std::size_t size(){ return elems.size(); }

    const Matrix_slice<N>& descriptor() const {desc;}

    T* data(){return elems.data();}

    const T* data() const {return elems.data();}

    Matrix_ref<T,N-1> operator[](std::size_t i){return row(i);}
    
    Matrix_ref<const T,N-1> operator[](const std::size_t i){return row(i);}

    Matrix_ref<T,N-1> row(std::size_t n);

    Matrix_ref<const T,N-1> row(std::size_t n) const;

    Matrix_ref<T,N-1> col(std::size_t n);

    Matrix_ref<const T,N-1> col(std::size_t n) const;

    template<typename...Args>
    Enable_if<Matrix_impl::Requesting_element<Args...>(),T&>
    operator()(Args...args);   //m(i,j,k) subscripting with integers

    template<typename...Args>
    Enable_if<Matrix_impl::Requesting_element<Args...>(),const T&>
    operator()(Args...args) const;   //m(i,j,k) subscripting with integers

    template<typename...Args>
    Enable_if<Matrix_impl::Requesting_slice<Args...>(),T&>
    operator()(Args...args);     // m(s1,s2,s3) subscripting with slices

    template<typename...Args>
    Enable_if<Matrix_impl::Requesting_slice<Args...>(),const T&>
    operator()(Args...args) const; // m(s1,s2,s3) subscripting with slices
    

    
  private:

    Matrix_slice<N> desc;
    std::vector<T> elems;    
  };
}

*/

int main()
{
  std::fstream ios{"hello.txt",std::ios_base::out};

  std::fstream* ios2=&ios;
  std::ostream& od(*ios2);
  
  od<<"hello";
}
