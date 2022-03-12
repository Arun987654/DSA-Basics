//Strongly Connected Components
#include<stdio.h>
#include<stdlib.h>

//Node definition for stack
struct node
{
	int item;
	struct node *next;
};

typedef struct node * ndptr;
ndptr topptr;          //One that points to top element of the stack

int clock=0;

//Structure defined for vertices
struct vertex
{
	int visited,entry,Exit,pred;
}V[100],W[100];

typedef struct vertex* vertices;

//Node definition for adjacency list
struct adjlistnode
{
	int key;
	struct adjlistnode* next;
};

typedef struct adjlistnode* nodeptr;

//Structure for adjacency list
struct adjlist
{
	nodeptr head;
};

typedef struct adjlist* list;

//Function that pushes val onto the stack
void push(int val)
{
	//Dynamically allocate memory to a new node 'newptr'
	ndptr newptr=(ndptr)malloc(sizeof(struct node));
	
	//When malloc() fails
	if(newptr==NULL)
	{
		printf("Push Failure\n");
		return;
	}
	
	//Push val onto the stack
	newptr->item=val;
	newptr->next=topptr;
	topptr=newptr;                         //Now this element will be at the top of the stack
}

//Function to perform pop operation on the stack
int pop()
{
	//When there is no element to be deleted
	if(topptr==NULL)
	{
		printf("Pop Failure\n");
		return -1;
	}
	
	//Create a temporary pointer for popping.
	//Initialise it to topptr
	ndptr tempptr=topptr;
	
	//Now make topptr point to the the element just below the top element in the stack
	topptr=topptr->next;
	
	//The link between tempptr and topptr is destroyed
	tempptr->next=NULL;
	
	//Store the element popped from the stack to a variable
	int var=tempptr->item;
	
	//Free the memory to avoid memory leak
	free(tempptr);
	
	//Return the popped element
	return var;
}

//A function to insert the neighbours of a vertex to the linked list corresponding to it
void insert(list ptr,int newval)
{
	nodeptr newnode = (nodeptr) malloc(sizeof(struct adjlistnode));
	newnode->key=newval;
	newnode->next=NULL;
	if(ptr->head==NULL)
	{
		ptr->head=newnode;
		return;
	}
	nodeptr curptr=ptr->head;
	while(curptr->next!=NULL)
		curptr=curptr->next;
	curptr->next=newnode;
}

//A recursive procedure of visiting vertices of the graph
//Will be called only if v is unvisited
void DFS_Explore(list ptr,vertices Q,int v,int check)
{
	
	//The vertex v is being visited , so assign 1
	Q[v].visited=1;     
	nodeptr curptr=ptr[v].head;
	
	if(!check)  //check will be 0 for G and 1 for G_reverse
	{
	    
		Q[v].entry=clock;         
		clock++;
	}
	else                           //Printing is required only when DFS_Explore is called for the reverse graph
		printf("%d",v+1);

	//Traverse the linked list
	//For each unvisited neighbour of v , call DFS_Explore recursively
	while(curptr)
	{
		int u=curptr->key;
		if(Q[u].visited==0)
		{
			Q[u].pred=v;
			if(check)
				printf(" ");
			DFS_Explore(ptr,Q,u,check);
		}
		curptr=curptr->next;
	}
	
	//Now,the exit time of vertex v will be the current value of clock
	if(!check)
	{
		Q[v].Exit=clock;
		
		//Push the vertex onto the stack
		//The stack will contain vertices such that the largest exit time vertex is on top of stack
		push(v);
		clock++;
	}
}

//Function to call DFS_Explore for each of the vertices if it is unvisited
void DFS(list ptr,int n)
{
	int v;
	for(v=0;v<n;v++)
	{
		if(V[v].visited==0)
			DFS_Explore(ptr,V,v,0);
	}
}

int main()
{
	int n,Vj,k,start,x;            //'start' is the starting vertex of DFS
	nodeptr curptr;
	
	//Get the input from the user
	scanf("%d",&n);
	
	//Create two arrays of structure 'adjlist' with size equal to the number of vertices
	//arr corresponds to G while arr_rev corresponds to G reverse
	struct adjlist arr[n],arr_rev[n];
	
	//Initialise the head pointers of each vertex to NULL
	for(k=0;k<n;k++)
	{
		arr[k].head=NULL;
		arr_rev[k].head=NULL;
		V[k].pred=-2;
		W[k].pred=-2;
	}
	
	//Construct adjacency list for G and G_reverse as per user's input
	for(k=0;k<n;k++)
	{
		scanf("%d",&Vj);
		while(Vj!=-1)
		{
			insert(&arr[k],Vj-1);                        //-1 is done so as to match array indices with vertex numbers
			insert(&arr_rev[Vj-1],k);		     //Since V={1,2.....n} and array index={0,1,.....n-1}	
			scanf("%d",&Vj);
		} 
	}
		
	//Call DFS_Explore with the starting vertex
	scanf("%d",&start);
	DFS_Explore(arr,V,start-1,0);
	DFS(arr,n);
	
	//Print the list of outneighbours of vertices in the reverse graph
	for(k=0;k<n;k++)
	{
		curptr=arr_rev[k].head;
		while(curptr)
		{
			printf("%d ",curptr->key+1);
			curptr=curptr->next;
		}
		printf("-1\n");	
	}
	
	//Print the strongly connected components of the input graph
	for(k=0;k<n;k++)
	{
		x=pop();
		if(W[x].visited==0)
		{
			DFS_Explore(arr_rev,W,x,1);         //Each time explore ends , a strong component is identified
			printf("\n");
		}
	}		
	return 0;
}
