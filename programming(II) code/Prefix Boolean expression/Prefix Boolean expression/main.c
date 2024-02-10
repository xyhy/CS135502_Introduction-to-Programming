//
//  main.c
//  Prefix Boolean expression
//
//  Created by 顏浩昀 on 2020/4/13.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>

char input[30];
int pos = 0;

int prefix(int a, int b, int c, int d){
    char x = input[pos++];
    int op1, op2;
    if(x == '&'){
        op1 = prefix(a, b, c, d);
        op2 = prefix(a, b, c, d);
        return op1&op2;
    }else if(x == '|'){
        op1 = prefix(a, b, c, d);
        op2 = prefix(a, b, c, d);
        return op1|op2;
    }else if(x=='A'){
        return a;
    }else if(x=='B'){
        return b;
    }else if(x=='C'){
        return c;
    }else if(x=='D'){
        return d;
    }
    return 0;
}


int main() {
    scanf("%s", input);
    for(int a = 0; a <= 1; a++){
        for(int b = 0; b <= 1; b++){
            for(int c = 0; c <= 1; c++){
                for(int d = 0; d <= 1; d++){
                    int out = prefix(a,b,c,d);
                    printf("%d %d %d %d %d\n", a, b, c, d, out);
                    pos = 0;
                }
            }
        }
    }
    return 0;
}
