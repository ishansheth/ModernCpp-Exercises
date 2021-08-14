#include <iostream>
#include <iomanip>

template<std::size_t N>
void rotateMatrix(int arr[N][N], int n)
{
  std::cout<<"Input:"<<std::endl;
  for(int i = 0;i<n;i++)
    {
      for(int j = 0; j<n;j++)
	std::cout<<std::setw(3)<<arr[i][j]<<" ";

      std::cout<<std::endl;
    }
  
  std::cout<<"-----------------------------------"<<std::endl;
  
  for(unsigned int j = 0 ; j<n/2; j++)
    {
      for(unsigned i = j; i<n-j-1; i++)
	{
	  int temp = arr[j][i]; 
	  arr[j][i] = arr[(n-1-j)-(i-j)][j];
	  arr[(n-1-j)-(i-j)][j] = arr[n-1-j][(n-1-j)-(i-j)];
	  arr[n-1-j][(n-1-j)-(i-j)] = arr[i][n-1-j];
	  arr[i][n-1-j] = temp;
	}      
    }

  std::cout<<"Output:"<<std::endl;

  for(int i = 0;i<n;i++)
    {
      for(int j = 0; j<n;j++)
	std::cout<<std::setw(3)<<arr[i][j]<<" ";
      
      std::cout<<std::endl;
    }

}

int main()
{
  
  int array1[1][1] = {{1}};
  rotateMatrix<1>(array1,1);
  std::cout<<"___________________________________________________"<<std::endl;
  
  int array2[2][2] = {{1,2},{3,4}};
  rotateMatrix<2>(array2,2);
  std::cout<<"___________________________________________________"<<std::endl;


  int array3[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
  rotateMatrix<3>(array3,3);
  std::cout<<"___________________________________________________"<<std::endl;
  

  int array4[4][4] = {{1,2,3,30},{4,5,6,60},{7,8,9,90},{10,11,12,120}};
  rotateMatrix<4>(array4,4);
  std::cout<<"___________________________________________________"<<std::endl;
  
  int array5[5][5] = {{1,2,3,30,20},{4,5,6,60,50},{7,8,9,90,80},{10,11,12,120,110},{13,14,15,150,140}};
  rotateMatrix<5>(array5,5);
  std::cout<<"___________________________________________________"<<std::endl;
  
}
