#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mx_;
bool ready;

void func1()
{
  mx_.lock();
  ready = true;
  mx_.unlock();
}

void func2()
{
  mx_.lock();
  if(ready)
    std::cout<<"ready is done"<<std::endl;
  else
    std::cout<<"ready is not done"<<std::endl;
  ready = false;
  mx_.unlock();
}


int main()
{

  for(;;)
    {
  std::thread t1(func2);
  std::thread t2(func1);

  t1.join();
  t2.join();

  std::this_thread::sleep_for(std::chrono::seconds(1));
    }

}
