//Doubly linked list
#include<stdio.h>
#include<stdlib.h>

//Node definition
struct node
{
	int item;
	struct node *next;
	struct node *prev;
};

typedef struct node * nodeptr;
int main()
{
	//Declaring structure pointers and variables
	nodeptr head=NULL,tail=NULL,curptr=NULL,temp=NULL;
	int n,key;
	scanf("%d",&n);
	
	//For loop that creates the doubly linked list
	for(int i=1;i<=n;i++)
	{
	
		//Dynamically allocate memory for the node pointer variable 'newptr'
		nodeptr newptr=(nodeptr) malloc(sizeof(struct node));
		
		//Get input from user and assign value to node
		scanf("%d",&key);
		newptr->item=key;
		
		//For adding the first node into the linked list
		if(head==NULL)
		{
		
			//'next' and 'prev' of first node should be NULL
			newptr->next=NULL;
			newptr->prev=NULL;
			
			//Since there is only one node, head=tail
			head=tail=newptr;
		}
		else
		{
		
			//Update the next pointer of tail as well as the previous pointer of newptr
			tail->next=newptr;
			newptr->prev=tail;
			
			//Now tail should point to the newly added node
			tail=newptr;
		}
	}

	//Print the resulting linked list from front to back
	curptr=head;
	while(curptr!=NULL)
	{
		printf("%d\n",curptr->item);
		curptr=curptr->next;
	}
	
	//Print the linked list from back to front
	curptr=tail;
	while(curptr!=NULL)
	{
		printf("%d\n",curptr->item);
		curptr=curptr->prev;
	}
	
	//Remove the first element of the list
	temp=head;
	head=head->next;           //Now head will point to the second element
	head->prev=NULL;
	free(temp);
	
	//Remove the last element of the list
	temp=tail;
	tail=tail->prev;          //Now tail will point to the second last element
	tail->next=NULL;
	free(temp);	
	
	//Print the resulting linked list from front to back
	curptr=head;
	while(curptr!=NULL)
	{
		printf("%d\n",curptr->item);
		curptr=curptr->next;
	}
	
	//Print the linked list from back to front 
	curptr=tail;
	while(curptr!=NULL)
	{
		printf("%d\n",curptr->item);
		curptr=curptr->prev;
	}
	return 0;
}
