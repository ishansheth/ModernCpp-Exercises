#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <iostream>
#include <future>

class ThreadPool
{
	unsigned int m_num_workers;
	std::vector<std::thread> m_worker_container;
	std::queue<std::function<void()>> m_task_queue;
	std::mutex	m_queue_mtx;	
	
	std::atomic<bool> stopped_pool;
	
	
public:
	ThreadPool(unsigned int x):m_num_workers(x),
				m_worker_container(std::vector<std::thread>(x)),
				stopped_pool(false)	
	{}	
	
	
	template<typename F,typename...Args>
	auto submit_task(F&& t,Args&&...arg) -> std::future<decltype(t(arg...))>
	{
		
		std::lock_guard<std::mutex> lock(m_queue_mtx);
		std::function<decltype(t(arg...))()> x1 = std::bind(std::forward<F>(t),std::forward<Args>(arg)...);		
		auto x2 = std::make_shared<std::packaged_task<decltype(t(arg...))()>>(x1);
		std::function<void()> temp = [x2]()
		{
			(*x2)();
		};
		
		m_task_queue.push(temp);	
		return x2->get_future();
	}	
	
	void start()
	{
		for(unsigned int i = 0; i < m_worker_container.size(); i++)
		{
			m_worker_container[i] = std::thread([this]()
			{				
				while(!stopped_pool)
				{
					std::lock_guard<std::mutex> lock(m_queue_mtx);				
					if(!m_task_queue.empty())
					{
						
						std::cout<<"in thread function...."<<std::this_thread::get_id()<<std::endl;
						auto func = m_task_queue.front();
						m_task_queue.pop();					
						func();				
					}
				}	
			});
		}
	}
	
	void stop()
	{
		stopped_pool = true;
		for(unsigned int i = 0; i < m_worker_container.size(); i++)
		{
			if(m_worker_container[i].joinable())
				m_worker_container[i].join(); 
		}	
	}
};

int multiply(int a,int b)
{
	return a*b;
}

int main()
{
	// create the thread pool
	ThreadPool t1(10);
	
	// start the pool and its worker threads
	t1.start();
	
	// submit 10 tasks to the pool
	for(int i = 0; i < 10; i++)
	{
		auto res = t1.submit_task(multiply,i,i+1);
		std::cout<<"thread pool task"<<res.get()<<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));	
	}
	
	// after 5 seconds stop the pool
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));		
	t1.stop();
}
