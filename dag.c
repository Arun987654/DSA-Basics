//Directed Acyclic Graph
#include<stdio.h>
#include<stdlib.h>

//Node definition for stack
struct node
{
	int item;
	struct node *next;
};

typedef struct node * ndptr;
ndptr topptr;

int clock=0;

//Structure defined for vertices
struct vertex
{
	int visited,entry,Exit,pred;
}V[100];

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

//Function that pushes the vertices onto the stack
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

//Function to pop vertices from the stack
void pop()
{
	//When there is no element to be deleted
	if(topptr==NULL)
	{
		printf("Pop Failure\n");
		return;
	}
	
	//Create a temporary pointer for popping.
	//Initialise it to topptr
	ndptr tempptr=topptr;
	
	//Now make topptr point to the the element just below the top element in the stack
	topptr=topptr->next;
	
	//The link between tempptr and topptr is destroyed
	tempptr->next=NULL;
	
	//Print the element popped from the stack (1 is added to match with the vertex number)
	printf("%d\n",tempptr->item+1);
	
	//Free the memory to avoid memory leak
	free(tempptr);
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
void DFS_Explore(list ptr,int v)
{

	//The vertex v is being visited , so assign 1
	V[v].visited=1;     
	
	//The entry time of vertex v is the current value of clock      
	V[v].entry=clock;  
	
	//Increment clock       
	clock++;
	
	nodeptr curptr=ptr[v].head;

	//Traverse the linked list
	//For each unvisited neighbour of v , call DFS_Explore recursively
	while(curptr)
	{
		int u=curptr->key;
		if(V[u].visited==0)
		{
			V[u].pred=v;
			DFS_Explore(ptr,u);
		}
		curptr=curptr->next;
	}
	
	//Now,the exit time of vertex v will be the current value of clock
	V[v].Exit=clock;
	push(v);           //To arrange in the order of decreasing exit times
	clock++;
}

//Function to call DFS_Explore for each of the vertices if it is unvisited
void DFS(list ptr,int n)
{
	int v;
	for(v=0;v<n;v++)
	{
		if(V[v].visited==0)
			DFS_Explore(ptr,v);
	}
}

int isdag(list ptr,int n)
{
	int u,k;
	//Here (k,u) belongs to E(G)
	for(k=0;k<n;k++)
	{
		nodeptr curptr=ptr[k].head;
		while(curptr)
		{
			u=curptr->key;
			
			//If G is a DAG, in every DFS of G , exit(u)<exit(k)
			//G contains a directed cycle iff every DFS on G produces a backedge
			if(V[k].Exit<V[u].Exit)         //If not , return 0 ---> Not a DAG
				return 0;	
			curptr=curptr->next;
		}
	}
	return 1;       //If G is a DAG
}

int main()
{
	int u,v,n,Vj,k,start;            //'start' is the starting vertex of DFS
	
	//Get the input from the user
	scanf("%d",&n);
	
	//Create an array of structure 'adjlist' with size equal to the number of vertices
	struct adjlist arr[n];
	
	//Initialise the head pointers of each vertex to NULL
	for(k=0;k<n;k++)
	{
		arr[k].head=NULL;
		V[k].pred=-2;
	}
	
	for(k=0;k<n;k++)
	{
		scanf("%d",&Vj);
		while(Vj!=-1)
		{
			insert(&arr[k],Vj-1);
			scanf("%d",&Vj);
		}
	}	
	
	//Call DFS_Explore with the starting vertex
	scanf("%d",&start);
	DFS_Explore(arr,start-1);
	DFS(arr,n);
	
	//Print entry time,exit time and predecessor
	for(k=0;k<n;k++)
			printf("%d %d %d\n",V[k].entry,V[k].Exit,V[k].pred+1);
			
	//Function call to check if it's a DAG or not
	if(isdag(arr,n)==0)
	{
		printf("Not a DAG\n");
		
		//Print the backedges
		//(u,v) is a backedge if entry(v)<entry(u)<exit(u)<exit(v)
		for(u=0;u<n;u++)
		{
			nodeptr curptr=arr[u].head;
			while(curptr)
			{
				v=curptr->key;
				if(V[v].entry<V[u].entry && V[u].Exit<V[v].Exit)
						printf("%d %d %d %d\n",V[v].entry,V[u].entry,V[u].Exit,V[v].Exit);
				curptr=curptr->next;
			}
		}
	}
	else
	{
		printf("DAG\n");
		
		//Now print the topological ordering ( Will be printed one by one inside pop() )
		for(k=0;k<n;k++)
			pop();
	}	
	return 0;
}
