// 二叉树
#if 0
struct bstree_node {
    int data;   // key
    struct bstree_node* left;
    struct bstree_node* right;

    // value
    long start;
    long end;
};

struct bstree{
    struct bstree_node* root;
};

struct bstree* tree;
#else
#include <stdio.h>
#include <stdlib.h>

typedef int KEY_VALUE;

#define BSTREE_ENTRY(name, type) \
        struct name{             \
            struct type* left;   \
            struct type* right;  \
        }

struct bstree_node {
    BSTREE_ENTRY(, bstree_node) bst;

    KEY_VALUE key;
    // value
    // 

};

struct bstree {
    struct bstree_node* root;
};

#endif
struct bstree_node* bstree_create_node(KEY_VALUE key){
    struct bstree_node* node = (struct bstree_node*)malloc(sizeof(struct bstree_node));
    if (node == NULL) {
        return NULL;
    }
    node->key = key;
    node->bst.left = node->bst.right = NULL;
    return node;
}

int bstree_insert(struct bstree* tree, int key){
    if(tree == NULL) return -1;

    if( tree->root == NULL ){
        tree->root = bstree_create_node(key);
        return 0;
    }

    struct bstree_node* node = tree->root;
    struct bstree_node* temp = tree->root;
    while (node != NULL){
        temp = node;
        if(key < node->key){
            node = node->bst.left;
        }
        else if(key > node->key){
            node = node->bst.right;
        }
        else{
            // ...
            return 1;
        }
    }
    // temp --> bstree_node
    // node == null
    if( key < temp->key ){
        temp->bst.left = bstree_create_node(key);
    }
    else{
        temp->bst.right = bstree_create_node(key);
    }
    return 0;
}

int bstree_traversal(struct bstree_node* node){
    if ( node == NULL ) return 0;
    bstree_traversal(node->bst.left);
    printf("%4d", node->key);
    bstree_traversal(node->bst.right);
}

#define ARRAY_LENGTH 15

int main(){
    int keys[ARRAY_LENGTH] = { 25, 68, 89, 90, 15, 78, 56, 69, 16, 26, 47, 10, 29, 61, 63 };
    struct bstree tree = { 0 };
    int i = 0;
    for(i = 0; i < ARRAY_LENGTH; i++){
        bstree_insert(&tree, keys[i]);
    }
    bstree_traversal(tree.root);
    return 0;
}