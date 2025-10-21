#include <stdio.h>
#include <time.h>
#include <conio.h>
long int sum_digit(long int x)
 { long int y=x,sum=0,r=0;
  int i=0;
  while (y!=0)
  {
    r=y%10;
    sum+=r;
    y/=10;
  }
   //只使用一个循环
   //不能再定义新的变量
  return sum;
 }
int main()
{ 
   clock_t start,end;
   double cost;
   long x=1234567,i=10000L;
   start=clock();
   while(i--)  sum_digit(x);
   end=clock();
   printf("sum(%ld)=%d\n",x,sum_digit(x));
   cost=(double)(end-start)/CLOCKS_PER_SEC;
   printf("%lf SECONDS pass!\n",cost);
} 