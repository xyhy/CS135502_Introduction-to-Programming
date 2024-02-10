//
//  main.c
//  Fairy Testing
//
//  Created by 顏浩昀 on 2020/4/13.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Type{AND, OR, VAR};

typedef struct _Node{
    enum Type type;
    int value;
    struct _Node *left, *right, *up;
}BTNode;

char prefix[100000000];
int pos = 0;
int lenth = 0;
int change;
BTNode *variety[200000];
BTNode *makenode(){
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    node->value = 0;
    node->left = node->right = node->up = NULL;
    return node;
}

int var(){
    int ret = 0;
    while(prefix[pos] != ']'){
        ret*=10;
        ret= ret + (int)(prefix[pos] - '0');
        pos++;
    }
    return ret;
}

BTNode *construct(BTNode *root){
    char c;
    BTNode *node = NULL;
    if(pos<lenth){
        c = prefix[pos++];
        if(c == '&'){
            node = makenode();
            node->type = AND;
            node->left = construct(node);
            node->right = construct(node);
            node->up = root;
        }else if(c == '|'){
            node = makenode();
            node->type = OR;
            node->left = construct(node);
            node->right = construct(node);
            node->up = root;
        }else if(c == '['){
            node = makenode();
            node->type = VAR;
            node->up = root;
            int x = var();
            variety[x] = node;
            pos++;
        }
    }
    return node;
}

int converse(int boolean){
    return !boolean;
}

void check(BTNode *node){
    if(node->type == VAR) node->value = converse(node->value);
    else if(node->type == AND){
        if(node->left->value == 1 && node->right->value == 1)  node->value = 1;
        else    node->value = 0;
    }else if(node->type == OR){
        if(node->left->value == 0 && node->right->value == 0)  node->value = 0;
        else    node->value = 1;
    }
    if(node->up != NULL){
        check(node->up);
    }else{
        printf("%d\n", node->value);
    }
}

void freetree(BTNode *root){
    if(root->left != NULL)  freetree(root->left);
    if(root->right != NULL) freetree(root->right);
    free(root);
}

int main() {
    int n = 0;
    scanf("%d", &n);
    while (n--) {
        pos = 0;
        int number = 0, times = 0;
        scanf("%d %d", &number, &times);
        memset(prefix, '0', 500000);
        scanf("%s", prefix);
        lenth = strlen(prefix);
        BTNode *root = NULL;
        root = construct(root);
        while (times--) {
            scanf(" %d", &change);
            check(variety[change]);
        }
        for(int i = 0; i < number; i++){
            variety[i] = NULL;
        }
        freetree(root);
    }
    return 0;
}
