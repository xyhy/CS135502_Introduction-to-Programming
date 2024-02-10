//
//  main.c
//  Sierpinski Carpet
//
//  Created by 顏浩昀 on 2019/11/11.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>

void divide(unsigned int iteration, long long int exist, long long int divided);
int main() {
    unsigned int  n = 0;
    scanf("%u", &n);
    divide(n,1,0);
    return 0;
}

void divide(unsigned int iteration,long long int new, long long int divided){
    if(iteration == 0)
        printf("0\n");
    else if(iteration == 1){
        printf("%lld\n", new + divided);
    }else{
        long long int divided2 = new+divided;
        new = new*8;
        divide(iteration-1, new, divided2);
    }
}
