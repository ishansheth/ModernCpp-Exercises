#include <iostream>
#include <utility>

class naive_vec
{
  int *ptr_;
  std::size_t size_;

public:
  naive_vec():ptr_(nullptr),size_(0){}
  ~naive_vec(){delete[] ptr_;}

  // copy ctor
  naive_vec(const naive_vec& other)
  {
    ptr_ = new int[other.size_];
    size_ = other.size_;
    std::copy(other.ptr_,other.ptr_+size_,ptr_);
  }

  // move ctor
  naive_vec(naive_vec&& other)
  {
    ptr_ = std::exchange(other.ptr_,nullptr);
    size_ = std::exchange(other.size_,0);
  }

  // copy assignment operator
  naive_vec& operator=(const naive_vec& other)
  {
    // copy and swap idiom which does not have a self-copy problem
    naive_vec copy(other);
    swap(copy,*this);
    return *this;
  }

  // move assignment operator
  naive_vec& operator=(naive_vec&& other)
  {
    // copy and swap idiom which does not have a self-copy problem
    naive_vec copy(std::move(other));
    swap(copy,*this);
    return *this;
  }
  
  friend void swap(naive_vec& vec1,naive_vec& vec2)
  {
    std::swap(vec1.ptr_,vec2.ptr_);
    std::swap(vec1.size_,vec2.size_);
  }
  
  void push_back(int newval)
  {
    int* newbuf = new int[size_ + 1];
    std::copy(ptr_,ptr_+size_,newbuf);
    delete[] ptr_;
    ptr_ = newbuf;
    ptr_[size_++] = newval;
  }

  void printElement(int i)
  {
    if(i < size_)
      std::cout<<ptr_[i]<<std::endl;
    else
      throw std::runtime_error("Out of index");
  }
  
};



int main()
{
  naive_vec vec1;
  vec1.push_back(1);
  vec1.push_back(2);

  {
    naive_vec vec2;
    vec2 = vec1;
    try
      {
	vec1.printElement(1);
	vec2.printElement(1); 
      }
    catch(std::exception& e)
      {
	std::cout<<e.what()<<std::endl;
      }
  }

}
