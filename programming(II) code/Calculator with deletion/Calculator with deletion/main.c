//
//  main.c
//  Calculator with deletion
//
//  Created by 顏浩昀 on 2020/4/14.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Type{PLUS, MINOR, PROUDUCT, VAR};
typedef struct _node{
    int id;
    long long int value;
    enum Type type;
    struct _node *left, *right, *up;
}Node;

char input[300005];
int pos = 0;
int len = 0;
int new_id = 1;
Node *root = NULL;

Node *makenode(){
    Node *node = (Node*)malloc(sizeof(Node));
    node->left = node->right = node->up = NULL;
    node->id = pos;
    return node;
}

Node *construct(Node *root){
    Node *node = NULL;
    char c;
    if(pos < len){
        c = input[pos++];
        if(c == '+'){
            node = makenode();
            node->type = PLUS;
            node->left = construct(node);
            node->right = construct(node);
            node->up = root;
        }else if(c == '-'){
            node = makenode();
            node->type = MINOR;
            node->left = construct(node);
            node->right = construct(node);
            node->up = root;
        }else if(c == '*'){
            node = makenode();
            node->type = PROUDUCT;
            node->left = construct(node);
            node->right = construct(node);
            node->up = root;
        }else{
            node = makenode();
            node->type = VAR;
            node->up = root;
            node->value = c - '0';
        }
    }
    return node;
}

void find(int num, Node **root, Node **store){
    while ((*root)->id != num) {
        if(((*root)->id < num) && ((*root)->right != NULL)){
            *root = (*root)->right;
        }else if((*root)->id > num){
            *root = (*root)->up->left;
        }
    }
    *store = *root;
}

void freetree(Node *node){
    if(node->left != NULL)  freetree(node->left);
    if(node->right != NULL) freetree(node->right);
    free(node);
}

void del(Node **del_from, Node **del_to_next){
    if((*del_from)->up != NULL){
        if((*del_from)->up->left == (*del_from)){
            (*del_from)->up->left = (*del_to_next);
            (*del_to_next)->up = (*del_from)->up;
        }else{
            (*del_from)->up->right = (*del_to_next);
            (*del_to_next)->up = (*del_from)->up;
        }
    }else{
        root = *del_to_next;
        (*del_to_next)->up = NULL;
    }
}

long long int print(Node *out){
    long long int leftside = 0, rightside = 0;
    long long int ans = 0;
    if(out->type == PLUS){
        leftside = print(out->left);
        rightside = print(out->right);
        ans = leftside + rightside;
        ans %= 10007;
    }else if(out->type == MINOR){
        leftside = print(out->left);
        rightside = print(out->right);
        ans = leftside - rightside;
        if(ans<0)   ans+=10007;
        ans %= 10007;
    }else if (out->type == PROUDUCT){
        leftside = print(out->left);
        rightside = print(out->right);
        ans = leftside * rightside;
        ans %= 10007;
    }else{
        ans = out->value;
    }
    return ans;
}

void newid(Node *root){
    root->id = new_id;
    if(root->left != NULL){
        new_id++;
        newid(root->left);
    }
    if(root->right != NULL){
        new_id++;
        newid(root->right);
    }
}

int main() {
    int n = 0;
    scanf(" %d", &n);
    scanf(" %s", input);
    len = strlen(input);
    Node *tmp = NULL;
    root = construct(root);
    while (n--) {
        tmp = root;
        char op;
        scanf(" %c", &op);
        if(op == 'D'){
            int idx1 = 0, idx2 = 0;
            scanf(" %d %d", &idx1, &idx2);
            Node *del_from = NULL, *del_to_next = NULL, *tmp2 = NULL;
            find(idx1, &tmp, &del_from);
            tmp2 = del_from;
            find(idx2+1, &tmp2, &del_to_next);
            del(&del_from, &del_to_next);
            free(del_from);
            newid(root);
            new_id = 1;
        }else if(op == 'Q'){
            int idx1 = 0;
            scanf(" %d", &idx1);
            Node *output = NULL;
            find(idx1, &tmp, &output);
            printf("%lld\n", print(output));
        }
    }
    freetree(root);
    return 0;
}
