//
//  main.c
//  Polynomial Calculator
//
//  Created by 顏浩昀 on 2019/10/3.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>

int main() {
    int degree = 0, x = 0;
    int sum = 0;
    scanf("%d%d", &degree, &x);
    int coefficient[degree];
    for(int a = 0; a <= degree; a++){
        int b = a;
        int c = 1;
        scanf("%d", &coefficient[a]);
        while((degree - b) > 0){
            c *= x;
            b++;
        }
        sum += (c * coefficient[a]);
    }
    printf("%d\n", sum);
    return 0;
}
