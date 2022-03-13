//C Program to implement a min-heap
#include<stdio.h>

int heapsize;

//A helper function to shift an element upwards until it reaches the appropriate position
void siftup(int h[],int pos)
{	
	//Swap the element with its parent until it becomes greater than its then parent	
	while(pos>0 && h[pos]<=h[(pos-1)/2])
	{
		int temp=h[pos];
		h[pos]=h[(pos-1)/2];                         //[(pos-1)/2] is parent(pos)
		h[(pos-1)/2]=temp;
		
		//Update the value of 'pos'
		pos=(pos-1)/2;
	}
}

//A helper function to shift an element downwards until it reaches the appropriate position
//Left and Right subtrees of 'pos' should be proper heaps 
void minheapify(int h[],int pos)
{
	if(2*pos+1>heapsize-1)                //Leaf node , nothing to be shifted
		return;
		
	int small=pos;
	
	//Find which among left and right child is smaller
	if(h[2*pos+1]<h[pos])
		small=2*pos+1;
	if(2*pos+2<=heapsize-1 && h[2*pos+2]<h[small])         //2*pos+1 is left(pos) and 2*pos+2 is right(pos)
		small=2*pos+2;
		
	//When both children are greater than the element , return
	if(small==pos)
		return;
		
	//Swap h[pos] and h[small]
	int temp=h[pos];
	h[pos]=h[small];
	h[small]=temp;
	
	minheapify(h,small);
}

//Function that outputs the minimum value in the heap
void findmin(int h[])
{
	printf("%d\n",h[0]);            //Minimum value will be at the the root position , ie , index 0
}

void insert(int h[],int key)
{
	if(heapsize==100)           //Array size limit exceeded
	{
		printf("Operation Fail\n");
		return;
	}
	
	//Increment heapsize
	heapsize++;
	
	//Add the element at the end of array and shift up using siftup() function
	h[heapsize-1]=key;
	siftup(h,heapsize-1);
}

//Function to decrease key value at position 'pos' to 'newval'
void decreasekey(int h[],int pos,int newval)
{
	if(h[pos]<=newval || pos>heapsize-1)
	{
		printf("Operation Fail\n");
		return;
	}
	
	//Change the key value at pos to newval and shift upwards
	h[pos]=newval;
	siftup(h,pos);
}

//Function to delete the node with the least value
int extractmin(int h[])
{
	//Store h[0] in a temp variable
	int temp=h[0];
	
	//Replace it with the last element of the array and call minheapify function to correct the ordering
	h[0]=h[heapsize-1];
	heapsize--;
	minheapify(h,0);
	
	//Return the deleted element
	return temp;
}

//Function that deletes element in the given index 'pos'
void delet(int h[],int pos)
{
	if(pos>heapsize-1)
	{
		printf("Operation Fail\n");
		return;
	}
	
	//Replace the element to be deleted with the last element and shift down
	h[pos]=h[heapsize-1];
	
	//Decrement heapsize to account for the one element that has been deleted
	heapsize--;
	minheapify(h,pos);
}

//Function to build heap from an unordered array
void buildheap(int h[])
{
	int index=heapsize/2;             //Highest index of a non-leaf node
	
	//Repeatedly call minheapify()
	for(int i=index;i>=0;i--)
		minheapify(h,i);
}

//Print the elements in increasing order of indices
void print(int h[])
{
	for(int i=0;i<heapsize;i++)
		printf("%d\n",h[i]);
}

int main()
{
	int A[100],choice,x,y,z,ind;
	scanf("%d",&heapsize);
	
	//Ask the user to input the elements of the heap
	for(int i=0;i<heapsize;i++)
		scanf("%d",&A[i]);
	buildheap(A);
	
	//While loop that executes until the user enters 7 (exit)
	while(1)
	{
		choice=7;
		//Ask the user to enter the choice ( 1-7 ) 
		scanf("%d",&choice);
		
		//Call the required function acc. to the value of 'choice'
		switch(choice)
		{
			case 1: scanf("%d",&x);
				insert(A,x);
				break;
				
			case 2: scanf("%d",&ind);
				delet(A,ind);
				break;
				
			case 3: printf("%d\n",extractmin(A));
				break;
				
			case 4: print(A);
				break;
				
			case 5: scanf("%d %d",&y,&z);
				decreasekey(A,y,z);
				break;
				
			case 6: findmin(A);
				break;
				
			default: return -1;
		}
	}
}
