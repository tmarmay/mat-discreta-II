#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rbt.h"

typedef struct node {
    u32 data;
    char color;
    struct node *left, *right, *parent;
} node;

static void LeftRotate(struct node **root,struct node *x) {
    if (!x || !x->right)
        return ;
    //y stored pointer of right child of x
    struct node *y = x->right;

    //store y's left subtree's pointer as x's right child
    x->right = y->left;

    //update parent pointer of x's right
    if (x->right != NULL)
        x->right->parent = x;

    //update y's parent pointer
    y->parent = x->parent;

    // if x's parent is null make y as root of tree
    if (x->parent == NULL)
        (*root) = y;

    // store y at the place of x
    else if (x == x->parent->left)
        x->parent->left = y;
    else    x->parent->right = y;

    // make x as left child of y
    y->left = x;

    //update parent pointer of x
    x->parent = y;
}

static void rightRotate(struct node **root,struct node *y) {
    if (!y || !y->left)
        return ;
    struct node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent =y->parent;
    if (x->parent == NULL)
        (*root) = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

static void insertFixUp(struct node **root,struct node *z) {
    // iterate until z is not the root and z's parent color is red
    while (z != *root && z != (*root)->left && z != (*root)->right && z->parent->color == 'R') {
        struct node *y;

        // Find uncle and store uncle in y
        if (z->parent && z->parent->parent && z->parent == z->parent->parent->left)
            y = z->parent->parent->right;
        else
            y = z->parent->parent->left;

        // If uncle is RED, do following
        // (i)  Change color of parent and uncle as BLACK
        // (ii) Change color of grandparent as RED
        // (iii) Move z to grandparent
        if (!y)
            z = z->parent->parent;
        else if (y->color == 'R') {
            y->color = 'B';
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent;
        }

        // Uncle is BLACK, there are four cases (LL, LR, RL and RR)
        else {
            // Left-Left (LL) case, do following
            // (i)  Swap color of parent and grandparent
            // (ii) Right Rotate Grandparent
            if (z->parent == z->parent->parent->left &&
                z == z->parent->left)
            {
                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent->parent);
            }

            // Left-Right (LR) case, do following
            // (i)  Swap color of current node  and grandparent
            // (ii) Left Rotate Parent
            // (iii) Right Rotate Grand Parent
            if (z->parent && z->parent->parent && z->parent == z->parent->parent->left &&
                z == z->parent->right)
            {
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                LeftRotate(root,z->parent);
                rightRotate(root,z->parent->parent);
            }

            // Right-Right (RR) case, do following
            // (i)  Swap color of parent and grandparent
            // (ii) Left Rotate Grandparent
            if (z->parent && z->parent->parent &&
                z->parent == z->parent->parent->right &&
                z == z->parent->right)
            {
                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                LeftRotate(root,z->parent->parent);
            }

            // Right-Left (RL) case, do following
            // (i)  Swap color of current node  and grandparent
            // (ii) Right Rotate Parent
            // (iii) Left Rotate Grand Parent
            if (z->parent && z->parent->parent && z->parent == z->parent->parent->right &&
                z == z->parent->left)
            {
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent);
                LeftRotate(root,z->parent->parent);
            }
        }
    }
    (*root)->color = 'B'; //keep root always black
}

set set_init() {
    set s = (set)malloc(sizeof(set_r));
    s->root = NULL;
    s->size = 0;
    return s;
}

void set_insert(set s, u32 data)
{
    ++s->size;
    // Allocate memory for new node
    struct node *z = (struct node*)malloc(sizeof(struct node));
    z->data = data;
    z->left = z->right = z->parent = NULL;

     //if root is null make z as root
    if (s->root == NULL)
    {
        z->color = 'B';
        s->root = z;
    }
    else
    {
        struct node *y = NULL;
        struct node *x = (s->root);

        // Follow standard BST insert steps to first insert the node
        while (x != NULL)
        {
            y = x;
            if (z->data < x->data)
                x = x->left;
            else if (z->data > x->data)
                x = x->right;
            else {
                --s->size;
                free(z);
                z = NULL;
                return;
            }
        }
        z->parent = y;
        if (z->data > y->data)
            y->right = z;
        else
            y->left = z;
        z->color = 'R';

        // call insertFixUp to fix reb-black tree's property if it
        // is voilated due to insertion.
        insertFixUp(&s->root,z);
    }
}

u32 set_size(set s) {
    return s->size;
}

static u32 hash_func(u32 num, u32 size) {
    return num%size;
}

void inorder(struct node* root, Grafo g, u32* next_free,
             vector* find_index, bool* used)
{
    static u32 last = 0;
    if (root == NULL)
        return;
    inorder(root->left, g, next_free, find_index, used);

    /* root->data es el elemento actual */
    u32 hash = hash_func(root->data,g->V);
    u32 h = next_free[hash];

    /* Busco una posicion que no este usada */
    while(used[h])
        h = hash_func(h+1,g->V);

    /* Asigno todos los valores necesarios */
    next_free[hash] = h;
    g->name[h] = root->data;
    used[h] = true;
    vector_pushback(find_index[hash],h);

    if (root->data < last)
        printf("\nPUTE\n");
    last = root->data;
    inorder(root->right, g, next_free, find_index, used);
}

static void set_destroy_r(struct node* node) {
    if (node == NULL)
        return;
    set_destroy_r(node->right);
    set_destroy_r(node->left);
    
    node->parent = NULL;
    free(node);
    node = NULL;
}

void set_destroy(set s) {
    set_destroy_r(s->root);
    free(s);
    s = NULL;
}
