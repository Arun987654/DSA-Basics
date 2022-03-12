//Depth First Search in an Undirected Graph
#include<stdio.h>
#include<stdlib.h>

//Global variables declaration
int visited[100],entry[100],Exit[100];
int clock=0;

//Node definition
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
	visited[v]=1;     
	
	//The entry time of vertex v is the current value of clock      
	entry[v]=clock;  
	
	//Increment clock       
	clock++;
	
	nodeptr curptr=ptr[v].head;

	//Traverse the linked list
	//For each unvisited neighbour of v , call DFS_Explore recursively
	while(curptr)
	{
		int u=curptr->key;
		if(visited[u]==0)
			DFS_Explore(ptr,u);
		curptr=curptr->next;
	}
	
	//Now,the exit time of vertex v will be the current value of clock
	Exit[v]=clock;
	clock++;
}

//Function to call DFS_Explore for each of the vertices if it is unvisited
void DFS(list ptr,int n)
{
	int v;
	for(v=0;v<n;v++)
	{
		if(visited[v]==0)
			DFS_Explore(ptr,v);
	}
}

int main()
{
	int n,m,Vi,Vj,k,start;            //'start' is the starting vertex of DFS
	
	//Get the input from the user
	scanf("%d %d",&n,&m);
	
	//Create an array of structure 'adjlist' with size equal to the number of vertices
	struct adjlist arr[n];
	
	//Initialise the head pointers of each vertex to NULL
	for(k=0;k<n;k++)
		arr[k].head=NULL;
	for(k=0;k<m;k++)
	{
		scanf("%d %d",&Vi,&Vj);
		
		//Add an edge from Vi to Vj and from Vj to Vi
		insert(&arr[Vi],Vj);						//Vj will be inserted to the linked list of Vi
		insert(&arr[Vj],Vi);				               //Vi will be inserted to the linked list of Vj
	}	
	//Call DFS_Explore with the starting verte
	DFS(arr,n);
	
	//Print entry and exit time of each vertex 
	//The entry and exit times would have been stored in the global arrays entry[] and Exit[] after the function calls are over 
	for(k=0;k<n;k++)
		printf("%d %d\n",entry[k],Exit[k]);
	return 0;
}
