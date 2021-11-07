#include <iostream>

void sortedSquares(int* arr, int size)
{
  int i=0,j=size-1;
  for(; i != j;)
    {
      if((arr[i]*arr[i]) > (arr[j]*arr[j]))
	{
	  std::cout<<(arr[i]*arr[i])<<std::endl;
	  i++;
	}
      else
	{
	  std::cout<<(arr[j]*arr[j])<<std::endl;
	  j--;
	}
    }

  std::cout<<(arr[i]*arr[i])<<std::endl;
}

int main()
{
  int arr[] = {2,4,5};
  sortedSquares(arr,sizeof(arr)/sizeof(arr[0]));

}
