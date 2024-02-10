#ifndef FUNCTION_H
#define FUNCTION_H
#include <stdio.h>
#include <ctype.h>
int solver(int **ptr, int *sum, char *s){
    int count = 0;
    int op = 0;
    int op2 = 0;
    while((*s) != '\0'){
        if(isdigit(*s) && isdigit(*(s+1))){
            ungetc(*s, stdin);
            scanf("%d", &op);
            op2 = op2*10 + op;
            s+=1;
        }else if(isdigit(*s) && (!isdigit(*(s+1)))){
            ungetc(*s, stdin);
            scanf("%d", &op);
            if(**ptr == -1){
                op2 = op2*10 + op;
                **ptr = -(op2);
            }else if(**ptr == 0){
                op2 = op2*10 + op;
                **ptr = op2;
            }
            *sum += (**ptr);
            ptr+=1;
            count+=1;
            s+=1;
            op2 = 0;
        }else if((*s) == '-'){
            **ptr = -1;
            s+=1;
        }else{
            s+=1;
        }
    }
    return count;
}
#endif

