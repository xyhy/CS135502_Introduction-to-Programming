//
//  main.c
//  Ugly Number
//
//  Created by 顏浩昀 on 2019/10/3.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>


int main() {
    int a;
    scanf("%d", &a);
    int input[a];
    int ugly = 1000000;
    int ugliest = 10000;
    for(int b = 0; b < a; b++){
        scanf("%d", &input[b]);
    }
    for(int c = 0; c < a; c++){
        int multiple = 0;
        int divisor = 0;
        for(int d = 0; d < a; d++){
            if((input[c] % input[d]) == 0){
                divisor += 1;
            }
            if((input[d] % input[c]) == 0){
                multiple += 1;
            }
        }
        if(((multiple - divisor) <= ugliest) && (input[c] < ugly)){
                ugly = input[c];
            ugliest = (multiple - divisor);
        }else if((multiple - divisor) < ugliest){
            ugly = input[c];
            ugliest = (multiple - divisor);
        }
    }
    printf("%d\n", ugly);
    return 0;
}
