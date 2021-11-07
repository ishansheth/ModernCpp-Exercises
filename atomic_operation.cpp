#include <atomic>
#include <thread>
#include <iostream>
#include <vector>

int x;

int func()
{
  return ++x;
}

int main()
{
  x=0;
  std::vector<std::thread> thread_pool(1000);

  for(auto& t: thread_pool)
    {
      t = std::thread([](){func();});
    }

  for(auto& t: thread_pool)
    {
      t.join();
    }

  std::cout<<x<<std::endl;

}
