#include <stdio.h> 
#include <time.h> 
#include <stdlib.h>

int guess; 
int main() 
{ 
   srand(time(NULL));
   int roll = rand() %1000 + 1; 
   printf("I have a number between 1 and 1000.\n"); 
   printf("Can you guess my number? \n");
   printf("Please type your first guess: \n");
   while (1)
   {
        if (scanf("%d", &guess) != 1)
        {
            printf("输入无效，请输入一个1到1000之间的整数：\n");
            // 清空输入缓冲区
            while (getchar() != '\n');
            continue;
        }

        if (guess < 1 || guess > 1000)
        {
            printf("猜测超出范围，请输入一个1到1000之间的整数：\n");
            continue;
        }  
        if (guess == roll)
        {
      printf("Excellent! You guessed the number.\n""Would you like to play again? (y/n) \n");
      char playAgain;
            // 读取并忽略之前的换行符
            scanf(" %c", &playAgain);
            if (playAgain == 'y' || playAgain == 'Y')
            {
                main();
            }
            break;
        }
    else if (guess < roll)
        {
      printf("Too low. Try again: ");
    }
    else
        {
      printf("Too high. Try again: ");
        }
      }
}
   