#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    TreeMap * newMap = (TreeMap *)malloc(sizeof(TreeMap));
    newMap->root = NULL;
    newMap->current = NULL;
    newMap->lower_than = lower_than;
    return newMap;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {   
    /* 
    Pair * z= (Pair *) malloc (sizeof(Pair));
    z = createTreeNode(key,value);
    TreeNode * y = NULL;
    TreeNode * x = tree->root;
    while (x != NULL){
        y = x;
        if (z->key < x->pair->key){
            x = x->left;
        }else x = x->right;
    }
    tree->current->parent = y;
    if (y == NULL){
        tree->root->pair = z;
    }else if(z->key<y->pair->key){
        y->left->pair = z;
    }
    return;
    */
}

TreeNode * minimum(TreeNode * x){
    TreeNode * aux = x;
    while (aux->left != NULL){
        aux=aux->left;
        
    }
    return aux;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    tree->root->left = NULL;
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode * aux = tree->root;
    while (aux != NULL){
        if (tree->lower_than(key,aux->pair->key) == 1){
            aux = aux->left;
        }else if(tree->lower_than(aux->pair->key,key) == 1){
            aux = aux->right;
        }else{
            tree->current=aux;
            return aux->pair;
        }
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    tree->current = tree->root;
    TreeNode * node = NULL;

    while (1){
        if (tree->lower_than(tree->current->pair->key,key) == 1){
            if (tree->current->right == NULL) break;

            tree->current = tree->current->right;
            continue;
        }

        if (tree->lower_than(tree->current->pair->key,key) == 0){
            if (tree->current->left == NULL) break;

            tree->current = tree->current->left;
            node = tree->current->parent;
            continue;
        }
    }

    if ( tree->lower_than(tree->current->pair->key,key) == 1 && node != NULL){
        return node->pair;
    }

    if (node == NULL){
        return NULL;
    }

    return tree->current->pair;
}

Pair * firstTreeMap(TreeMap * tree) {
    TreeNode* first=minimum(tree->root);
    tree->current=first;
    return first->pair;
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    TreeNode * aux = tree->current;
    //TreeNode * otroaux = aux->parent;
    if (aux->right != NULL){
    aux = minimum(aux->right);
    tree->current=aux;
    return aux->pair;
    }

    TreeNode * z = tree->current->parent;
    while(z != NULL){
        if (tree->lower_than(tree->current->pair->key, z->pair->key)){
            tree->current = z;
            return tree->current->pair;
        }else{
            z=z->parent;
        }
    }
    return NULL;

       
    /*
    while (otroaux != NULL && aux != otroaux->right){
        otroaux=otroaux->parent;
    }
    tree->current = otroaux;
    return otroaux->pair;
    */
}

