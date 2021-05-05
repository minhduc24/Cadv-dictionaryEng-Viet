#include<stdio.h>
#include<stdlib.h>

/*int check(int**a,int x,int y,int n)
{
  for(int i=0;i<x;i++)
    for(int j=0;j<y;j++)
      {
	if(n==a[x][y])
	  return 1;
	else return 0;
      }
      }*/

int find(int a[][4],int x,int y,int u,int v)
{
  if(u>x)
    return 0;
  else if(v>y)
    return 0;
  else return a[u][v];
}

void display(int a[][4],int x,int y)
{
  int k=0;
  for(int i=0;i<x;i++)
    for(int j=0;j<y;j++)
      {
	if(a[i][j]==0)
	  printf("X\t");
	else if(a[i][j]==1||a[i][j]==2)
	  printf("-\t");
	else if(a[i][j]==3)
	  printf("O\t");
	k++;
	if(k%4==0)
	  printf("\n");
      }
}

int nearby(int a[][4],int x,int y,int u,int v)
{
  int dem=0;
  /*if(u>x)
    return 0;
  else if(v>y)
  return 0;*/
  for(int i=u-1;i<u+2;i++)
    for(int j=v-1;j<v+2;j++)
      {
	if(a[i][j]==2)
	    dem++;
      }
  return dem;
}

void main()
{
  int i,j,m,n=0;
  int x,y;
  int a[4][4];
  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      a[i][j]=1;
  a[1][0]=2;a[3][2]=2;
  printf("Display Map:\n");
  display(a,4,4);
  for(m=1;m<7;m++)
    {
      printf("Your target?");
      scanf("%d%*c%d%*c",&y,&x);
      if(y>4||x>4)
	{
	  printf("WRONG SYNTAX!!! TRY AGAIN\n");
	  return;
	}
      if(find(a,4,4,y,x)==1)
	{
	  a[y][x]=0;
	  display(a,4,4);
	  printf("You missed\n");
	  printf("%d enemy(s) around\n",nearby(a,4,4,y,x));
	  printf("%d rockets left\n",5-m);
	  printf("%d enemy(s) left\n",2-n);
	  if(m==5)
	    {
	      printf("YOU LOSE\n");
	      break;
	    }
	}
      else if(find(a,4,4,y,x)==2)
	{
	  a[y][x]=3;
	  n++;
	  display(a,4,4);
	  printf("You hit\n");
	  printf("%d enemy(s) around\n",nearby(a,4,4,y,x));
	  printf("%d rockets left\n",5-m);
	  printf("%d enemy(s) left\n",2-n);
	  if(n==2)
	    {
	      printf("YOU WON\n");
	      break;
	    }
	  if(m==5)
	    {
	      printf("YOU LOSE\n");
	      break;
	    }
	}
    }
  return;
}
  
