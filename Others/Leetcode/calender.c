#include<stdio.h>

int main(int argc, char const *argv[])
{
    int numbdays = 0;
    int startingday = 0;
    printf("Enter the number of days in the month");scanf("%d", &numbdays);
    printf("Enter the starting day (0= sunday, 1= monday, dll)");scanf("%d", &startingday);
    int count = 1 + startingday;
    printf("S  M  T  W  T  F  S\n");

      for (int i = 0; i != startingday; i++)
        {
            printf("   ");
        }
    
        for (int i = 1; i <= numbdays; i++)
        {
            printf("%d", i);
            if (i < 10)
            {
                printf("  ");
            } else {
                printf(" ");
            }
            


            if (count == 7)
            {
                printf("\n");
                count = 0;
            }
            count++;
            
        }
        

    

    


    return 0;
}

