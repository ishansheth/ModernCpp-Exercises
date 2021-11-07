#include <iostream>

void findSubArray(int* array, int size,int sum)
{
  int indices[2] = {0,0};

  int sub_length = indices[1] - indices[0];
  
  int left=0,right=0;

  int sub_sum = array[left];
  
  for(;right<size;)
    {      
      if(sub_sum == sum)
	{
	  if((right - left) > sub_length)
	    {
	      sub_length = right -left;
	      indices[0] = left+1;
	      indices[1] = right+1;
	    }
	  right++;
	  sub_sum += array[right];
	  
	}
      else if(sub_sum > sum)
	{
	  sub_sum -= array[left];	  
	  left++;
	}
      
      else if(sub_sum < sum)
	{
	  right++;
	  sub_sum += array[right];
	}
    }

  std::cout<<indices[0]<<":"<<indices[1]<<std::endl;
}

int main()
{
  int arr[] = {1,2,3,4,5,0,0,0,6,7,8,9,10};
  findSubArray(arr,sizeof(arr)/sizeof(arr[0]),9);

}
