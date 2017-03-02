#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Tree_node{
  struct Tree_node *left, *right;
  int data;
} Tree_node;

/* part : iterative version */
int isBST_iter(Tree_node *tree){
  Tree_node *cur = tree, *pre = NULL, *tmp;
	while (cur != NULL){
		if (cur->left == NULL){
      if (pre != NULL && pre->data >= cur->data){
        return 0;
      }
      pre = cur;
      cur = cur->right;
    }
    else{
      tmp = cur->left;
      while(tmp->right != NULL && tmp->right != cur)
          tmp = tmp->right;
      if(tmp->right == NULL) { // left child has not been visited
          tmp->right = cur;
          cur = cur->left;
      }
      else { // left child has been visited already
          tmp->right = NULL;
          if(pre != NULL && pre->data >= cur->data) 
              return 0;
          pre = cur;
          cur = cur->right;
      }
    }
			return 0;
	}
  return 1;


}


/*partb: recursive version*/

int isBSTUtil(Tree_node* tree, int min, int max) 
{ 
  /* an empty tree is BST */
  if (tree == NULL) 
     return 1;
       
  /* false if this node violates the min/max constraint */ 
  if (tree->data < min || tree->data > max) 
     return 0; 
 
  /* otherwise check the subtrees recursively, 
   tightening the min or max constraint */
  return
    isBSTUtil(tree->left, min, tree->data-1) &&  // Allow only distinct values
    isBSTUtil(tree->right, tree->data+1, max);  // Allow only distinct values
} 

int isBST_recur(Tree_node *tree){
	return isBSTUtil(tree, INT_MIN, INT_MAX);	
}

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
Tree_node *newNode(int data)
{
  Tree_node* node = (Tree_node*) malloc(sizeof(Tree_node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
 
  return(node);
}

/*
int main(){
  Tree_node *root   = newNode(3);
  root->left        = newNode(2);
  root->right       = newNode(5);
  root->left->left  = newNode(1);
  root->left->right = newNode(4); 
 
  if(isBST_iter(root))
    printf("Is BST\n");
  else
    printf("Not a BST\n");
     
  getchar();
  return 0;
} 
*/