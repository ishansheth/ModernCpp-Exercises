/*
  An example of the atomic operation
*/

#include <atomic>
#include <thread>
#include <iostream>
#include <vector>

// creating an atomic variable with type as int
std::atomic<int> x;
// creating non atomic variable with type as int
int y;

void func()
{
  // increamenting both
  ++y;
  ++x;
}

int main()
{
  x=0;
  y=0;

  // thread pool, vector of 1000 thread objects
  std::vector<std::thread> thread_pool(1000);

  for(auto& t: thread_pool)
    {
      // creating thread object and put it in a container
      t = std::thread([](){func();});
    }

  for(auto& t: thread_pool)
    {
      // joining all threads in thread pool
      t.join();
    }

  // after the 1000 thread exection, x = 1000 and y = undefined 
  std::cout<<"Atomic x:"<<x<<std::endl;
  std::cout<<"Non Atomic y:"<<y<<std::endl;

}
