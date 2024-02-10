#ifndef FUNCTION_H
#define FUNCTION_H

typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} Node;

void constructTree(Node** head);
void printInfix(Node *root){
    if(root->data == '&' || root->data == '|'){
        if((root->right->data == '|' || root->right->data <= '&')){
            printInfix(root->left);
            printf("%c", root->data);
            printf("(");
            printInfix(root->right);
            printf(")");
        }
        else{
            printInfix(root->left);
            printf("%c", root->data);
            printInfix(root->right);
        }
    }
    else if(root->data >= 'A' && root->data <= 'D'){
        printf("%c", root->data);
    }
}
void freeTree(Node *root);

#endif
