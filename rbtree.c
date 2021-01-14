#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1
typedef int KEY_TYPE;

typedef struct rbtree_node {
    unsigned char color;
    struct rbtree_node* parent;
    struct rbtree_node* left;
    struct rbtree_node* right;
    KEY_TYPE key;

    // value
} rbtree_node;

typedef struct rbtree {
    rbtree_node* root;
    rbtree_node* nil; // NULL
} rbtree;

// rotate
void rbtree_left_rotate(rbtree* T, rbtree_node* x){
    // NULL --> T->nil
    if( x == T->nil ) return;
    rbtree_node* y = x->right;
    x->right = y->left;
    if ( y->left != T->nil ){
        y->left->parent = x;
    }

    y->parent = x->parent;
    if( x->parent == T->nil ){
        T->root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rbtree_right_rotate(rbtree* T, rbtree_node* y){
    // NULL --> T->nil
    if( y == T->nil ) return;
    rbtree_node* x = y->left;
    y->left = x->right;
    if ( x->right != T->nil ){
        x->right->parent = y;
    }

    x->parent = y->parent;
    if( y->parent == T->nil ){
        T->root = x;
    }
    else if(y == y->parent->right){
        y->parent->right = x;
    }
    else{
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;

}

void rbtree_insert_fixup(rbtree* T, rbtree_node* z){
    // z->color == RED
    // z->parent->color == RED

    // z --> RED
    rbtree_node* y;
    while( z->parent->color == RED ){
        if(z->parent == z->parent->parent->left){
            y = z->parent->parent->right;
            if(y->color == RED){
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                y->color = BLACK;

                z = z->parent->parent;
            }
            else{
                if ( z = z->parent->right ){
                    z = z->parent;
                    rbtree_left_rotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbtree_right_rotate(T, z->parent->parent);
            }
        }
        else if( z->parent == z->parent->parent->right ){
            y = z->parent->parent->left;
            if( y->color == RED){
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                y->color = BLACK;

                z = z->parent->parent;
            }
            else{
                if ( z = z->parent->left ){
                    z = z->parent;
                    rbtree_right_rotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbtree_left_rotate(T, z->parent->parent);
            }
        }
    }
}

void rbtree_insert(rbtree* T, rbtree_node* z){

    rbtree_node* y = T->nil;
    rbtree_node* x = T->root;
    while(x != T->nil){
        y = x;
        if( z->key < x->key ){
            x = x->left;
        }
        else if( z->key > x->key ){
            x = x->right;
        }
        else{ //Exist
            return;
        }
    }

    z->parent = y;
    if( y == T->nil ){
        T->root = z;
    }
    else if( z->key < y->key ){
        y->left = z;
    }
    else{
        y->right = z;
    }

    // z --> 
    z->color = RED;
    z->left = T->nil;
    z->right = T->nil;

    rbtree_insert_fixup(T, z);

}