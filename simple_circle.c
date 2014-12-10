#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main()
{
int i, j;

for(i = -10; i < 10; i++) 
{
  for(j = -10; j < 10; j++)
  {
    if(i*i + j*j < 100)
      printf("*");
    else
      printf(" ");
  }
  printf("\n");
}


  return 0;
}
