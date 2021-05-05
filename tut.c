#include<stdio.h>
#include<stdlib.h>

void main()
{
  int k=0;
  for(int i=0;i<4;i++)
    for(int j=0;j<4;j++)
      {
	printf("L\t");
	k++;
	if(k%4==0)
	  printf("\n");
      }
}
