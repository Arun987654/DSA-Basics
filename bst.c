//Binary Search Tree
#include<stdio.h>
#include<stdlib.h>

//Node definition
struct node
{
	int key;
	struct node *right;
	struct node *left;
	struct node *parent;
};

typedef struct node * nodeptr;
nodeptr root=NULL,cur=NULL,prev=NULL;

//Function to search if an element is present in the BST or not
nodeptr search(nodeptr root,int x)
{
	//Base case
	if(root==NULL || root->key ==x)        //if root is NULL , the the element is not present
		return root;
		
	//Recursively search left subtree
	if(x<root->key)                        
		return search(root->left,x);
		
	//Recursively search right subtree
	return search(root->right,x);
}

//Function to insert an element into the BST
nodeptr insert(nodeptr root,int x)
{
	nodeptr newptr= (nodeptr) malloc(sizeof(struct node));
	if(newptr==NULL)
		return NULL;
	newptr->key=x;
	newptr->left=NULL;
	newptr->right=NULL;
	newptr->parent=NULL;
	int dir;                  //To keep track of the direction ( left or right )
	if(root==NULL)
		return newptr;
	prev=NULL;
	cur=root;
	while(cur!=NULL)
	{
		//Go to the left subtree if x is less than or equal to current key , right subtree otherwise
		//Update the value of 'dir' accordingly
		if(x<cur->key)
		{
			prev=cur;
			cur=cur->left;
			dir=0;
		}
		else
		{
			prev=cur;
			cur=cur->right;
			dir=1;
		}
	}	
	
	//Add the new node acc. to the value of dir
	if(dir==0)
		prev->left=newptr;
	else
		prev->right=newptr;
		
	//Parent node is just the previous node ; prev's left or right points to newptr
	newptr->parent=prev;
	return root;
}

//Function for performing an inorder traversal (left,root,right)
void inorder(nodeptr root)
{
	if(root==NULL)
		return;
		
	//Recursively call left subtree
	inorder(root->left);
	printf("%d\n",root->key);
	
	//Recursively call right subtree
	inorder(root->right);
}

//Function for performing preorder traversal (root,left,right)
void preorder(nodeptr root)
{
	if(root==NULL)
		return;
	printf("%d\n",root->key);
	
	//Recursively call left subtree
	preorder(root->left);
	
	//Recursively call right subtree
	preorder(root->right);
}

//Function for performing postorder traversal (left,right,root)
void postorder(nodeptr root)
{
	if(root==NULL)
		return;
		
	//Recursively call left subtree
	postorder(root->left);
	
	//Recursively call right subtree
	postorder(root->right);
	printf("%d\n",root->key);
}

//To find prdecessor of an element
nodeptr pred(nodeptr p)
{
	//No predecessor case
	if(p==NULL)
		return NULL;
		
	//If left subtree has atleast one node
	if(p->left!=NULL)
	{
		cur=p->left;
		//To find the max value in the left subtree , go to its rightmost end
		while(cur->right!=NULL)
			cur=cur->right;
		return cur;
	}
	
	//Otherwise, travel upwards ( parent nodes ) to find the predecessor
	cur=p;
	prev=cur->parent;
	while(prev!=NULL && cur==prev->left)
	{
		cur=prev;
		prev=cur->parent;
	}
	return prev;
}

//To find successor of an element
nodeptr succ(nodeptr p)
{
	//No successor case
	if(p==NULL)
		return NULL;
		
	//If right subtree has atleast one node
	if(p->right!=NULL)
	{
		cur=p->right;
		//To find the min value in the right subtree , go to its leftmost end
		while(cur->left!=NULL)
			cur=cur->left;
		return cur;
	}
	
	//Otherwise, travel upwards ( parent nodes ) to find the predecessor
	cur=p;
	prev=cur->parent;
	while(prev!=NULL && cur==prev->right)
	{
		cur=prev;
		prev=cur->parent;
	}
	return prev;
}

//Helper function to print output message of delet function
void errormsg()
{
	printf("Deletion Fail\n");
}

//Function to delete an element from the bst
//Returns the root of the updated bst
nodeptr delet(nodeptr root,int x)
{
	//Search for the node containing x 
	nodeptr del_ptr=search(root,x);
	
	//If search function returns NULL , then print Deletion Fail and return
	if(del_ptr==NULL)
	{
		errormsg();
		return root;
	}
	
	//When the node has both left and right subtrees empty
	if(del_ptr->right==NULL && del_ptr->left==NULL)
	{
	
		//If it is the root node , then bst will become empty after deletion
		if(del_ptr->parent==NULL)
		{
			free(del_ptr);
			return NULL;
		}
		
		//Otherwise , make del_ptr's parent's chils as NULL
		if(del_ptr==del_ptr->parent->right)
			del_ptr->parent->right=NULL;
		if(del_ptr==del_ptr->parent->left)
			del_ptr->parent->left=NULL;
		free(del_ptr);
		return root;
	}
	
	//When the node has exactly one child and its right subtree is empty
	if(del_ptr->right==NULL && del_ptr->left!=NULL)
	{
		//If it is the root node, make del_ptr->left as the root and free the memory
		if(del_ptr->parent==NULL)
		{
			del_ptr->left->parent=NULL;
			root=del_ptr->left;
			free(del_ptr);
			return root;
		}
		
		//Make del_ptr's left as del_ptr's parent's child
		if(del_ptr==del_ptr->parent->right)
			del_ptr->parent->right=del_ptr->left;
		else
			del_ptr->parent->left=del_ptr->left;
		del_ptr->left->parent=del_ptr->parent;
		free(del_ptr);
		return root;
	}
	
	//When the node has exactly one child and its left subtree is empty
	if(del_ptr->right!=NULL && del_ptr->left==NULL)
	{
		//If it is the root node, make del_ptr->right as the root and free the memory
		if(del_ptr->parent==NULL)
		{
			del_ptr->right->parent=NULL;
			root=del_ptr->right;
			free(del_ptr);
			return root;
		}
		
		//Make del_ptr's right as del_ptr's parent's child
		if(del_ptr==del_ptr->parent->right)
			del_ptr->parent->right=del_ptr->right;
		else
			del_ptr->parent->left=del_ptr->right;
		del_ptr->right->parent=del_ptr->parent;
		free(del_ptr);
		return root;
	}
	
	//When the node has two children
	if(del_ptr->right!=NULL && del_ptr->left!=NULL)
	{
	
		//Replace del_ptr with its inorder predecessor
		
		nodeptr sptr=pred(del_ptr);
		int ptemp=sptr->key;            //Storing the predecessor value in a temporary variable
		
		//Now delete the predecessor node recursively
		delet(root,sptr->key);
		
		//Update key value to 'ptemp'
		del_ptr->key=ptemp;
		return root;
	}
}

int main()
{
	int choice,y;
	nodeptr ptr=NULL,tempptr=NULL;
	
	//While loop that executes until the user enters 9 (exit)
	while(1)
	{
	
		//Ask the user to enter the choice ( 1-9 ) 
		scanf("%d",&choice);
		
		//Call the required function acc. to the value of 'choice'
		switch(choice)
		{
			case 1: scanf("%d",&y);
				root=insert(root,y);
				if(root==NULL)
					printf("Insert Fail\n");
				break;
				
			case 2: scanf("%d",&y);
				if(search(root,y)==NULL)
					printf("Not Found\n");
				else
					printf("Found\n");
				break;
				
			case 3: inorder(root);
				break;
				
			case 4: preorder(root);
				break;
				
			case 5: postorder(root);
				break;
				
			case 6: scanf("%d",&y);
				ptr=search(root,y);
				if(ptr!=NULL)
				{
					tempptr=pred(ptr);
					if(tempptr!=NULL)
						printf("%d\n",tempptr->key);
					else
						printf("No predecessor\n");
				}
				else
					printf("Invalid Input\n");
				break;
				
			case 7: scanf("%d",&y);
				ptr=search(root,y);
				if(ptr!=NULL)
				{
					tempptr=succ(ptr);
					if(tempptr!=NULL)
						printf("%d\n",tempptr->key);
					else
						printf("No successor\n");
				}
				else
					printf("Invalid Input\n");
				break;
				
			case 8: scanf("%d",&y);
				root=delet(root,y);
				break;
				
			default: exit(1);
		}
	}
	return 0;
}
