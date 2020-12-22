#include<stdio.h>

int main()
{
  int h;
  do{

   printf("Height: ");// taking height until user don't coperates
   scanf("%d", &h);

  }
  while(h>8||h<1);

   for (int i = 1; i <= h ; i++)
   {
     for(int j = 0 ; j<= h-1-i ; j++)  // process of pyramid
     {
     printf(" ");// printing space to make it look like pyramid
     }
     for(int j = -i ; j <= i ; j++ )
     {
         if( j==0 )  // printing space in middle portion
        {
         printf("  ");
        }else
       printf("#");
     }
     printf("\n");// to change line after every row
   }
   return 0;
}
