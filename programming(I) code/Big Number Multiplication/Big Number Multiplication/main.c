//
//  main.c
//  Big Number Multiplication
//
//  Created by 顏浩昀 on 2019/10/28.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>


int first4(int x){
    return x/10000;
}
int last4(int x){
    return x%10000;
}

int main() {
    int a,b,c,d,e,f;
    char input[16];
    int converse[16] = {0};
    int new_input[4] = {0};
    int output[8] = {0};
    for(int a = 0; a < 16; a++){
        scanf("%c", &input[a]);
        converse[a] = (int)(input[a] - '0');
    }
    new_input[0] = converse[0]*1000+converse[1]*100+converse[2]*10+converse[3];
    new_input[1] = converse[4]*1000+converse[5]*100+converse[6]*10+converse[7];
    new_input[2] = converse[8]*1000+converse[9]*100+converse[10]*10+converse[11];
    new_input[3] = converse[12]*1000+converse[13]*100+converse[14]*10+converse[15];
    // let a 16-digit part to four 4-digit number.
    output[7] = last4(new_input[3]*new_input[3]);
    a = first4(new_input[3]*new_input[3]) + last4(2*new_input[3]*new_input[2]);
    output[6] = last4(a);
    b = last4(new_input[2]*new_input[2]) + last4(2*new_input[3]*new_input[1]) + first4(2*new_input[3]*new_input[2]) + first4(a);
    output[5] = last4(b);
    c = first4(new_input[2]*new_input[2]) + last4(2*new_input[3]*new_input[0]) + last4(2*new_input[2]*new_input[1]) + first4(2*new_input[3]*new_input[1]) + first4(b);
    output[4] = last4(c);
    d = first4(2*new_input[3]*new_input[0]) + first4(2*new_input[2]*new_input[1]) + last4(2*new_input[0]*new_input[2]) + last4(new_input[1]*new_input[1]) + first4(c);
    output[3] = last4(d);
    e = first4(2*new_input[2]*new_input[0]) + first4(new_input[1]*new_input[1]) + last4(2*new_input[0]*new_input[1]) + first4(d);
    output[2] = last4(e);
    f = first4(2*new_input[0]*new_input[1]) + last4(new_input[0]*new_input[0]) + first4(e);
    output[1] = last4(f);
    output[0] = first4(new_input[0]*new_input[0]) + first4(f);
    printf("%4d", output[0]);
    for(int i = 1; i < 8; i++){
        printf("%04d", output[i]);
    }
    printf("\n");
    return 0;
}
