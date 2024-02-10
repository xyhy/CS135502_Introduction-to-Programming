//
//  main.c
//  Construct a binary tree
//
//  Created by 顏浩昀 on 2020/4/13.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    int data;
    struct _Node *left, *right;
}BTNode;

int idx = 0;
int num = 0;

BTNode* makeNode(int a){
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    node->data = a;
    node->left = node->right = NULL;
    return node;
}

BTNode* construct(int in[], int *pre, int start, int end){
    BTNode *node = NULL;
    if(idx < num){
        int node_pos = in[pre[idx]];
       //printf("%d %d %d %d\n", pre[idx], node_pos, start, end);
        node = makeNode(pre[idx++]);
        if(idx < num){
            if(idx >= num)  return node;
            if(in[pre[idx]] < node_pos && in[pre[idx]] >= start && in[pre[idx]] <= end){
                node->left = construct(in, pre, start, node_pos-1);
                //printf("left side return %d %d %d\n", idx, start, end);
            }
            if(idx >= num)  return node;
            if(in[pre[idx]] > node_pos && in[pre[idx]] >= start && in[pre[idx]] <= end){
                node->right = construct(in, pre, node_pos+1, end);
                //printf("right side return %d %d %d\n", idx, start, end);
            }
        }
    }
    return node;
}

void printpostorder(BTNode *root){
    if(root->left != NULL) printpostorder(root->left);
    if(root->right != NULL) printpostorder(root->right);
    printf("%d ", root->data);
}

void freetree(BTNode *root){
    if(root->left != NULL) freetree(root->left);
    if(root->right != NULL) freetree(root->right);
    free(root);
}

int main() {
    scanf(" %d", &num);
    int *inorder = (int*)malloc(num * sizeof(int));
    int *preorder = (int*)malloc(num * sizeof(int));
    int inorder_map[200005];
    for(int i = 0; i < num; i++){
        scanf(" %d", &inorder[i]);
        inorder_map[inorder[i]] = i;
    }
    for(int i = 0; i < num; i++){
        scanf(" %d", &preorder[i]);
    }
    int startidx = 0, endidx = num-1;
    BTNode *root = construct(inorder_map, preorder, startidx, endidx);
    printpostorder(root);
    printf("\n");
    freetree(root);
    return 0;
}

/* TLE : let inorder have a map that inorder[1] = 3 -> inorder_map[3] = 1.
            compare between inorder_map[preorder[pos]] and inorder_map[preorder[pos+1]]*/
