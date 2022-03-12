//C Program to solve Tower Of Hanoi Game
#include<stdio.h>

//Function to print the disk movements
//To transfer n disks from pole p1 to pole p3 , using intermediate pole p2
void tower(int n,int p1,int p2,int p3)
{
	if(n<1)
		return;

	//Base Case
	if(n==1)
	{
		printf("Move Disk %d from Pole %d to Pole %d\n",n,p1,p3);
		return;
	}
	
	tower(n-1,p1,p3,p2);
	printf("Move Disk %d from Pole %d to Pole %d\n",n,p1,p3);
	tower(n-1,p2,p1,p3);
}

int main()
{
	int n;
	
	//Input the value of n
	scanf("%d",&n);
	
	//Function Call
	tower(n,0,1,2);
	return 0;
}
