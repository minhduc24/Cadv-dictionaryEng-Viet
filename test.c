#include<stdio.h>
#include<stdlib.h>

void main()
{
  int i;
  for(i=0;i<100;i++)
    {
      if(i%3==0&&i%5==0)
	printf("ĐMM\n");
      else if(i%3==0)
	printf("DM\n");
      else if(i%5==0)
	printf("D\n");
      else printf("_\n");
    }
}
