#include<stdio.h>
#include<stdlib.h>

//Node definition
struct node
{
	int item;
	struct node *next;
};

typedef struct node * nodeptr;

//front and back declared as a global variable so as to use it inside all functions
nodeptr front,back;

int isempty()
{
	//if front is NULL, return 1 otherwise return 0
	return (front==NULL);          
}

void enqueue()
{
	//Dynamically allocate memory to a new node 'newptr'
	nodeptr newptr=(nodeptr)malloc(sizeof(struct node));
	
	//When malloc() fails
	if(newptr==NULL)
	{
		printf("Enqueue Failure\n");
		return;
	}
	
	//Get the element to be added to the queue from user and add it to the node
	scanf("%d",&(newptr->item));
	
	//If queue is empty , then now it'll contain one element , so front and back are equal
	if(isempty())
		front=back=newptr;
		
	//In a queue , insertion takes place at the back, so add newptr at the end and update 'back'
	else
	{
		back->next=newptr;
		back=newptr;
	}                         
}

void dequeue()
{
	//When there is no element to be removed
	if(isempty())
	{
		printf("Dequeue Failure\n");
		return;
	}
	
	//Element is to be removed from front
	
	//Create a temporary pointer for dequeue operation
	//Initialise it to front
	nodeptr tempptr=front;
	
	//Now make front point to the next node
	front=front->next;
	
	//The link between tempptr and front is destroyed
	tempptr->next=NULL;
	
	//Print the element removed from the queue
	printf("%d\n",tempptr->item);
	
	//Free the memory to avoid memory leak
	free(tempptr);
}

void peek()
{

	//If the list is non-empty , print the item pointed to by front
	if(!isempty())
		printf("%d\n",front->item);
}

void display()
{
	if(isempty())
	{
		printf("Empty List\n");
		return;
	}
	
	//If the linked list is non-empty,traverse it and print the elements of queue from front to back
	nodeptr curptr=front;
	while(curptr!=NULL)
	{
		printf("%d\n",curptr->item);
		curptr=curptr->next;
	}
}

int main()
{
	int choice;
	
	//While loop that executes until the user enters 5 (exit)
	while(1)
	{
	
		//Ask the user to enter the choice ( 0-5 ) 
		scanf("%d",&choice);
		
		//Call the required function acc. to the value of 'choice'
		switch(choice)
		{
			case 0: if(isempty())               //isempty() returns 1 if the list is empty
					printf("Empty\n");
				else
					printf("Non Empty\n");
				break;
				
			case 1: enqueue();
				break;
				
			case 2: dequeue();
				break;
				
			case 3: peek();
				break;
				
			case 4: display();
				break;
				
			case 5: exit(0);
		}
	}
	return 0;
}
