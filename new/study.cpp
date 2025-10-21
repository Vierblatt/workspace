// #include <stdio.h>
// int add(int a, int b);
// int sub(int a, int b);
// int mul(int a, int b);
// int div(int a, int b);

// //函数指针&数组


// int main() {
//    /* int a[10]={0};
//     int len=sizeof(a)/sizeof(int);
//     for(int i=0;i<len;i++) {
//         printf("%d ",a[i]);
//     } */
// int (*arr[4])(int , int )={add,sub,mul,div};
// printf("Enter two numbers: ");
// int a,b;
// scanf("%d %d",&a,&b);
// int choice;
// printf("Enter choice (1-add, 2-sub, 3-mul, 4-div): ");
// scanf("%d",&choice);
// int result=arr[choice-1](a,b);
// printf("Result: %d",result);
// return 0;
//     }
   
// int add(int a, int b) {
//     return a+b;
// }
// int sub(int a, int b) { 
//     return a-b;
// }   
// int mul(int a, int b) {
//     return a*b;
// }
// int div(int a, int b) {
//     return a/b;
// }
//字符串数组
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