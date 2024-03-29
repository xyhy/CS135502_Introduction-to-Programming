#include <stdio.h>
#include "12719.h"

int n;
int preOrder[MAX_N];

int main() 
{
    int T; scanf("%d", &T);
    for(int t = 0; t < T; t++)
    {
        printf("test %d : \n", t);
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
            scanf("%d", &preOrder[i]);
        Node *root = buildBST(n, preOrder);
        /*
        printtest(root);
        printf("\n");
        */
        printInOrder(root);
        printf("\n");
        printPostOrder(root);
        printf("\n");
        freeTree(root);
    }
}

