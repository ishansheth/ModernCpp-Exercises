#include <iostream>
struct chunk
{
	int i;
	chunk* next;
	chunk(int x):i(x){next = nullptr;}
	chunk(){next = nullptr;}
};
class stack
{
	chunk* head;
	int num;
	int max_size = 10;
public:
	stack()
	{
		head = new chunk;
		head->next = nullptr;
		num = 0;
	}
	
	stack(int j)
	{
		head = new chunk(j);
		head-> next = nullptr;
		num = 1;
	}
	
	~stack(){clear();}
	
	int top(){return head->i;}
	
	void pop()
	{
		chunk* temp = head;
		head = head->next;
		num--;
		delete temp;
	}
	
	void push(int i)
	{
	    if(num == 0)
	    {
	        head = new chunk(i);
	        head->next = nullptr;
	        num++;
	        return;
	    }
	    if(num < max_size)
	    {
    		chunk* temp = new chunk(i);
	    	temp->next = head;
		    head = temp;
		    num++;			
	    }else{
	        std::cout<< "limit of the stack is reached:"<<i<<" can not be interted"<<std::endl;
	    }
	}
	
	void clear()
	{
	    std::cout<<"clearing "<<num<<"elements"<<std::endl;
	    for(int i = num;i>0;i--){pop();}	    
	}
	
	int size() const{return num;}
	
	void print()
	{
	    std::cout<<"Printing stack:";
		chunk* temp = head;
		while(temp)
		{
			std::cout<<temp->i<<" ";
			temp = temp->next;
		}
		std::cout<<"\n";
		delete temp;
	}
	bool full(){return (num == max_size);}
	bool empty(){return (num == 0);}
};


int main(int argc, char* argv[])
{

	stack s(1);s.push(2);
	s.print();
	std::cout<<"first time size:"<<s.size()<<std::endl;
	std::cout<<"top element:"<<s.top()<<std::endl;
	std::cout<<"poping:"<<std::endl;
	s.pop();
	std::cout<<"top element:"<<s.top()<<std::endl;
	s.push(3);	s.push(4);	s.push(5);	s.push(6);	s.push(7);	
	s.push(8);	s.push(9);	s.push(10);	s.push(11);	s.push(12);	
	s.push(13);	s.push(14);	
	std::cout<<"top element:"<<s.top()<<std::endl;
	s.print();s.pop();s.pop();
	std::cout<<"top element:"<<s.top()<<std::endl;
	s.clear();
	std::cout<<"cleared, now size:"<<s.size()<<std::endl;
	std::cout<<"pushing"<<std::endl;
	s.push(100);
	std::cout<<"size:"<<s.size()<<std::endl;
	std::cout<<"top:"<<s.top()<<std::endl;
	
}