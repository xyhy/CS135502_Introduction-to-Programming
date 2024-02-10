#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000006

typedef struct Node
{
    int key;
    struct Node *ltree;
    struct Node *rtree;
} Node ;

int max = 2000500000, min = -1;
int pos = 0;
// build a binary search tree with given pre-order traversal
// return pointer to root
Node *buildBST(int n, int *preOrder){
    int max_l = preOrder[pos], min_l = min, max_r = max, min_r = preOrder[pos];
    Node *node = NULL;
    if(pos < n){
        node = (Node*)malloc(sizeof(Node));
        node->key = preOrder[pos];
        node->ltree = node->rtree = NULL;
        //printf("A pos : %d %d %d %d %d %d\n", pos, node->key, min_l, max_l, min_r, max_r);
        if( (preOrder[pos+1] > max_l || preOrder[pos+1] < min_l) && (preOrder[pos+1] < min_r || preOrder[pos+1] > max_r) )  return node;
        else{
            if(preOrder[pos+1] > min_l && preOrder[pos+1] < max_l){
                max = node->key;
                min = min_l;
                pos++;
                //printf("B pos : %d Max : %d  Min: %d\n", pos,max,min);
                node->ltree = buildBST(n, preOrder);
                //printf("C pos : %d Max : %d  Min: %d Return left to %d\n", pos,max,min,node->key);
            }
            if(preOrder[pos+1] > min_r && preOrder[pos+1] < max_r){
                min = node->key;
                max = max_r;
                pos++;
                //printf("D pos : %d Max : %d  Min: %d\n", pos,max,min);
                node->rtree = buildBST(n, preOrder);
                //printf("E pos : %d Max : %d Min : %d Return right to %d\n", pos,max,min,node->key);
            }
        }
    }
    return node;
}

/*
void printtest(Node *root){
    if(root->ltree == NULL && root->rtree == NULL){
        printf("value : %d\n", root->key);
    }
    else if(root->ltree != NULL && root->rtree == NULL){
        printf("value : %d left : %d\n", root->key, root->ltree->key);
    }
    else if(root->ltree == NULL && root->rtree != NULL){
        printf("value : %d right : %d\n", root->key, root->rtree->key);
    }
    else{
        printf("value : %d left : %d right : %d\n", root->key, root->ltree->key, root->rtree->key);

    }
    if(root->ltree != NULL) printtest(root->ltree);
    if(root->rtree != NULL) printtest(root->rtree);
}

*/

// print the in-order traversal of a given tree
// it is suggested to implement using recursion
void printInOrder(Node *ptr){
    if(ptr->ltree != NULL)  printInOrder(ptr->ltree);
    printf("%d ", ptr->key);
    if(ptr->rtree != NULL) printInOrder(ptr->rtree);
}

// print the post-order traversal of a given tree
// it is suggested to implement using recursion
void printPostOrder(Node *ptr){
    if(ptr->ltree != NULL)  printPostOrder(ptr->ltree);
    if(ptr->rtree != NULL) printPostOrder(ptr->rtree);
    printf("%d ", ptr->key);
}

// delete the binary search tree in case of memory leak
// it is suggested to implement using recursion
void freeTree(Node *ptr){
    max = 2000500000;
    min = -1;
    pos = 0;
    if(ptr->ltree != NULL)  freeTree(ptr->ltree);
    if(ptr->rtree != NULL)  freeTree(ptr->rtree);
    free(ptr);
}

#endif // FUNCTION_H_


/* Hint : For each node, we need to know the max and min border, and if the next value is bigger than max one, return to previous node and do it again.*/

// MLE???
