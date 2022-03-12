//C Program to implement Quick Sort eliminating tail recursion
#include<stdio.h>

//Function for pivot partitioning
long partition(long arr[],long left,long right,long k)
{
	long temp,i=left-1;
	for(long j=left;j<right;j++)
	{
		if(arr[j]<arr[k])
		{
			i++;
			temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
		}
	}
	temp=arr[i+1];
	arr[i+1]=arr[right];
	arr[right]=temp;
	return i+1;
}

//Function to perform quick sort
void quick_sort(long arr[],long left,long right)
{
	while(left<right)
	{
		long index=partition(arr,left,right,right);
		quick_sort(arr,left,index-1);
		left=index+1;
	}
}

int main()
{
	long n,i;
	scanf("%ld",&n);
	long arr[n];
	for(i=0;i<n;i++)
		scanf("%ld",&arr[i]);
		
	//Function Call
	quick_sort(arr,0,n-1);
	
	//Print the sorted array , one element per line
	for(i=0;i<n;i++)
		printf("%ld\n",arr[i]);
	return 0;
}
