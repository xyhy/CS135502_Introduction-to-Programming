//
//  main.c
//  prefix
//
//  Created by 顏浩昀 on 2019/11/10.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>

float prefix(void);

int main(void){
    int n = 0;
    scanf("%d", &n);
    for(int a = 0; a<n; a++){
        float ans = prefix();
        int integer = ans;
        if(integer != ans){
            printf("= %.1f\n", ans);
        }else{
            printf("= %d\n", integer);
        }
    }
    return 0;
}

float prefix(void)
{
    char c;
    float ans;
    float op1, op2;
    while(isspace(c = getchar())) continue;
    if(c == '+'){
        printf("( ");
        op1 = prefix();
        printf("+ ");
        op2 = prefix();
        printf(") ");
        ans = op1 + op2;
    }else if(c == '-'){
        printf("( ");
        op1 = prefix();
        printf("- ");
        op2 = prefix();
        printf(") ");
        ans = op1 - op2;
    }else if (c == '*'){
        printf("( ");
        op1 = prefix();
        printf("* ");
        op2 = prefix();
        printf(") ");
        ans = op1 * op2;
    }else if (c == '/'){
        printf("( ");
        op1 = prefix();
        printf("/ ");
        op2 = prefix();
        printf(") ");
        ans = op1 / op2;
    }else if(isdigit(c)){
        ungetc(c, stdin);
        scanf("%f", &ans);
        printf("%.0f ", ans);
    }
    return ans;
}

