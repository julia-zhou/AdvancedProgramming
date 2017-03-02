#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree_node{
	struct tree_node *left, *right;
	char *key;
	char *def;
}tree_node;

tree_node *create_node(char* key, char* def){
  tree_node *node = malloc(sizeof(tree_node));
  node ->key = key;
  node -> def = def;
  return node;
}

tree_node *create_tree(){ 
   tree_node *node = malloc(sizeof(tree_node));
   node->left = NULL; 
   return( node ); 
}

/*delete word remove word from dictionary. print success or failure message to screen.*/
tree_node *delete(tree_node *tree, char *delete_key){

	tree_node  *tmp_node, *upper_node, *other_node, *deleted_object;

    if( tree->left == NULL ){
      return( NULL);
    }else if( tree->right == NULL ){
     	if (strcmp(tree->key, delete_key) == 0){
     		deleted_object = tree->left;
      		tree->left = NULL;
      		return( deleted_object );
    	}
    	else{
      		return( NULL );
      	}
    }else{
	    tmp_node = tree;
	    while( tmp_node->right != NULL ){
	      upper_node = tmp_node;
	      if( strcmp(delete_key,tmp_node->key)<0 ){
	        tmp_node   = upper_node->left;
	        other_node = upper_node->right;
	      }
	      else{
	        tmp_node   = upper_node->right;
	        other_node = upper_node->left;
	      }
    	}
		if( strcmp(tmp_node->key, delete_key) != 0 ){
	      return( NULL );
		}else{
	      upper_node->key   = other_node->key;
	      upper_node->left  =  other_node->left;
	      upper_node->right = other_node->right;
	      deleted_object = tmp_node->left;
	      free( tmp_node ); 
	      free( other_node ); 
	      return( deleted_object );
	    }
	}
}

/* add word "definition" add the given word and associated definition to the dictionary. print success or failure message to screen */
int insert(tree_node  *tree, char *new_key, tree_node *new_object){
	tree_node  *tmp_node;

	if( tree->left == NULL ){
	    tree->left = new_object;
	    tree->key  = new_key;
	    tree->right  = NULL;
	  }
	else{
	    tmp_node = tree;
	    while( tmp_node->right != NULL ){
	      if( strcmp(new_key,tmp_node->key)<0 ){
	        tmp_node = tmp_node->left;
	      }else{
	        tmp_node = tmp_node->right;
	      }
	    }

		if ( tmp_node->key == new_key ){
	    	return( -1 );
	    }
	 	tree_node *old_leaf, *new_leaf;
	        
        old_leaf = malloc(sizeof(tree_node));
        old_leaf->left = tmp_node->left;
        old_leaf->key = tmp_node->key;
        old_leaf->right  = NULL;
        new_leaf = malloc(sizeof(tree_node));
        new_leaf->left =  new_object;
        new_leaf->key = new_key;
        new_leaf->right  = NULL;
        if( strcmp(tmp_node->key, new_key)<0 ){   
            tmp_node->left  = old_leaf;
            tmp_node->right = new_leaf;
            tmp_node->key = new_key;
          }
        else{   
            tmp_node->left  = new_leaf;
            tmp_node->right = old_leaf;
          }
      }
}

/*find word find definition associated with input word and print to screen*/
tree_node *find(tree_node  *tree,  char* query){
  if( tree->left == NULL || (tree->right == NULL && strcmp(tree->key,query) != 0 ) ){
  	
    return(NULL);
  }else if (tree->right == NULL && strcmp(tree->key,query) == 0 ){
  	
    return( tree->left );
  }else{
    if( strcmp(tree->key,query) >0 ){
    	
      return( find(tree->left, query) );
    }else{
    	
    	return( find(tree->right, query) );
    }
  }
}

/*print show the contents of the dictionary in key order*/
void print_tree(tree_node *tree) {
   if (tree == NULL) return;
   if (tree->right == NULL){
   	printf("(%s,%s)\n",tree->left->key, tree->left->def);
   	return;
   }
   print_tree(tree->left);   
   print_tree(tree->right);
} 

int main (int argc, char **argv){
  /*
  tree_node *root = create_node("e", NULL);
  root -> left = create_node("c", NULL);
  root -> right = create_node("g", NULL);
  root -> left->left = create_node("c", "ccc");
  root -> left -> right= NULL;
  root -> right -> left= create_node("e", NULL);
  root -> right -> right = create_node("g", NULL);
  root -> right -> left->left= create_node("e", "eee");
  root -> right -> left->right = NULL;
  root -> right -> right -> left = create_node("g", "ggg");
  root -> right -> right -> right = NULL;
  */
  tree_node *root = create_tree();
  //while (strcmp(argv[1],"end") !=0){
  if (strcmp(argv[1], "add")== 0 && argc == 4){
    tree_node *new_object = create_node(argv[2], argv[3]);
    
    char *new_key = argv[1];
    int a = insert(root, new_key, new_object);
    if (a == -1){
      printf("Failure: the key already exists\n");
    }else{
      printf("Success!\n");
      //print_tree(root);
    }

  }else if (strcmp(argv[1], "delete")== 0 && argc == 3){
    char *key = argv[2];
    tree_node *node = delete(root, key);
    if (node == NULL){
      printf("Failure: the key does not exist.\n");
    }else{
      printf("Success!\n"); 
      //print_tree(root);
    }
  }else if (strcmp(argv[1], "find")== 0 && argc == 3){
    char *key = argv[2];
    tree_node *node = find(root, key);
    if (node == NULL){
      printf("Failure: the key does not exist.\n");
    }else{
      printf("The definition is %s\n",node->def);
      free(node);
    }

  }else if (strcmp(argv[1], "print")== 0){
    if (root->left != NULL){
    print_tree(root);
    free(root);
    }else{
      printf("Tree is empty\n");
    }
  }else{
    printf("Incorrect input. Try again.\n");
  }
  //}
  return 0;
 }


