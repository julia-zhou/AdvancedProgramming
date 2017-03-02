#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct rb_node{
  struct tree_node *left, *right;
  int red;
  char *key;
  char *def;
}rb_node;

typedef struct rb_tree{
  rb_node *root;
};


int is_red(rb_node *root){
    return root != NULL && root->red == 1;
}

rb_node *rota_single(rb_node *root, int dir)
{
  if (dir = 0){
    rb_node *save = root->right;

    root->right = save->left;
    save->left = root;
  }else{
    rb_node *save = root->left;

    root->left = save->right;
    save->right = root;
  }
    root->red = 1;
    save->red = 0;

    return save;
}

rb_node *rota_double(rb_node *root, int dir)
{
  if (dir = 0){
    root->right = rota_single(root->right, !dir);
  }else{
    root->left = rota_single(root->left, !dir);
  }

  return rota_single(root, dir);
}



rb_node *make_node(char* data)
{
    rb_node *rn = malloc(sizeof(rb_node));

    if (rn != NULL)
    {
        rn->key = data;
        rn->def = NULL;
        rn->red = 1; /* 1 is red, 0 is black */
        rn->left = NULL;
        rn->right = NULL;
    }

    return rn;
}

rb_node *insert_r(rb_node *root, char* data)
{
    if (root == NULL)
    {
        root = make_node(data);
    }
    else if (strcmp(data,root->data) != 0)
    {
        int dir = root->data < data;

        if (dir = 0){
          root->left = insert_r(root->left, data);
        }else{
          root->right = insert_r(root->right, data);
        }

        

        if (is_red(root->))
        {
            if (is_red(root->link[!dir]))
            {
                /* Case 1 */
                root->red = 1;
                root->link[0]->red = 0;
                root->link[1]->red = 0;
            }
            else
            {
                /* Cases 2 & 3 */
                if (is_red(root->link[dir]->link[dir]))
                {
                    root = jsw_single(root, !dir);
                }
                else if (is_red(root->link[dir]->link[!dir]))
                {
                    root = jsw_double(root, !dir);
                }
            }
        }else{

        }
    }

    return root;
}

int jsw_insert(rb_tree *tree, char* data)
{
    tree->root = insert_r(tree->root, data);
    tree->root->red = 0;

    return 1;
}
/*
int rb_assert(rb_node *root)
{
    int lh, rh;

    if (root == NULL)
    {
        return 1;
    }
    else
    {
        rb_node *ln = root->left;
        rb_node *rn = root->right;

        /* Consecutive red links 
        if (is_red(root))
        {
            if (is_red(ln) || is_red(rn))
            {
                puts("Red violation");
                return 0;
            }
        }

        lh = rb_assert(ln);
        rh = rb_assert(rn);

        /* Invalid binary search tree 
        if ((ln != NULL && strcmp(ln->key, root->key)>=0) || (rn != NULL && strcmp(ln->key, root->key)<=0)
        {
            puts("Binary tree violation");
            return 0;
        }

        /* Black height mismatch 
        if (lh != 0 && rh != 0 && lh != rh)
        {
            puts("Black violation");
            return 0;
        }

        /* Only count black links 
        if (lh != 0 && rh != 0)
        {
            return is_red(root) ? lh : lh + 1;
        }
        else
        {
            return 0;
        }
    }
}
*/



