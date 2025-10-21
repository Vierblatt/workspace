#define _CRT_SECURE_NO_WARNINGS 1
#include<stdbool.h>
#include<stdio.h>
#define MAX 100

int main()
{
    int floor[50][50] = { 0 };
    int x = 0, y = 0;
    int k,s=1,step,face=1;//1是上，2是右，3是下，4是左
    bool key = false;
    while (s == 1)
    {
        printf("Enter command(9 to end input): ");
        scanf("%d", &k);
        if (k == 1) 
        {
            key = 0;
        }
        if (k == 2)
        {
            key = 1;
        }
        if (k == 3)
        {
            face = face + 1;
            if (face > 4)
                face = 1;
        }
        if (k == 4)
        {
            face = face - 1;
            if (face < 1)
                face = 4;
        }
        if (k == 5)
        {
            printf("Enter step to walk:");
            scanf("%d", &step);
            int nx = x, ny = y;
            for (int i = 0; i < step; i++) 
            {
                switch (face)
                {
                case 1: nx -= 1; break; 
                case 2: ny += 1; break; 
                case 3: nx += 1; break; 
                case 4: ny -= 1; break; 
                }

                if (nx >= 0 && nx < MAX && ny >= 0 && ny < MAX)
                {
                    floor[nx][ny] = 1;
                }
            }
            x = nx;
            y = ny;
        }
        if (k == 6)
        {
            printf("The drawing is:\n");
            for (int i = 0; i < 50; i++)
            {
                for (int e = 0; e < 50; e++)
                {
                    if (floor[i][e] == 1)
                    {
                        printf("* ");
                    }
                    else
                    {
                        printf("  ");
                    }
                }
                printf("\n");
            }
        }
        if (k == 9) 
        {
            s = 0;
        }
    }
}