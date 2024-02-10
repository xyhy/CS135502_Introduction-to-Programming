//
//  main.c
//  Remove unnecessary parentheses
//
//  Created by 顏浩昀 on 2020/4/12.
//  Copyright © 2020 顏浩昀. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXEXPR 256
#define NUMSYM 6
// This code is transfer infix to sytnax tree, then reading tree again and print by inorder.
char expr[MAXEXPR];  // string to store the input expression.
int pos;             // current position of parsing, from end to start

char sym[NUMSYM];

typedef struct _Node {
    char data;
    struct _Node *left, *right;
} BTNode;

BTNode* makeNode(char);
BTNode* EXPR(void);
BTNode* FACTOR(void);
void freeTree(BTNode *root);
void printPrefix(BTNode *root);

BTNode* makeNode(char c){
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    for(int i = 0; i < NUMSYM; i++){
        if(c == sym[i]){
            node->data = sym[i];
            break;
        }
    }
    node->left = NULL;
    node->right = NULL;
    return node;
}

BTNode* EXPR(){
    char c;
    BTNode *node=NULL, *right=NULL;
    if(pos>=0){
        right = FACTOR();
        if(pos>0){
            c = expr[pos];
            if(c=='&' || c=='|'){
                node = makeNode(c);
                node->right = right;
                pos--;
                node->left = EXPR();
            }else{
                node = right;
            }
        }else{
            node = right;
        }
    }
    return  node;
}

BTNode* FACTOR(){
    char c;
    BTNode *node=NULL;
    c = expr[pos--];
    if(c>='A' && c<='D'){
        node = makeNode(c);
    }else if(c == ')'){
        node = EXPR();
        pos--;
    }
    return node;
}

int main(void){
    sym[0]='A';
    sym[1]='B';
    sym[2]='C';
    sym[3]='D';
    sym[4]='&';
    sym[5]='|';
    scanf("%s", expr);
    pos = strlen(expr) - 1;
    BTNode *root = EXPR();
    printPrefix(root);
    freeTree(root);

    return 0;
}

/* print a tree by In-order. */
void printPrefix(BTNode *root){
    if(root->data == '|' || root->data == '&'){
        if(root->right->data == '|' || root->right->data == '&'){
            printPrefix(root->left);
            printf("%c", root->data);
            printf("(");
            printPrefix(root->right);
            printf(")");
        }else{
            printPrefix(root->left);
            printf("%c", root->data);
            printPrefix(root->right);
        }
    }else if(root->data >= 'A' && root->data <= 'D'){
        printf("%c", root->data);
    }
}

/* clean a tree.*/
void freeTree(BTNode *root){
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

