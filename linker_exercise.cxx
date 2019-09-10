#include <cstdio>

typedef int(*FT)(const void*,const void*);

extern "C"{
  typedef int (*CFT)(const void*,const void*);
  void qsort(void* p,std::size_t n,std::size_t sz,CFT cmp);
}

void f(){
  printf("inside f");
}

int main(){
  f();
}
