//
//  main.c
//  Little Brick's Functions
//
//  Created by 顏浩昀 on 2019/10/24.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>

int gcd(int a, int b);
int lcm(int a, int b);
int power(int a, int b);
int main() {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    printf("%d\n", gcd(lcm(power(a, b), c), d));
    printf("%d\n", gcd(power(lcm(a, b), c), d));
    printf("%d\n", lcm(gcd(power(a, b), c), d));
    printf("%d\n", lcm(power(gcd(a, b), c), d));
    printf("%d\n", power(gcd(lcm(a, b), c), d));
    printf("%d\n", power(lcm(gcd(a, b), c), d));
    return 0;
}


int gcd(int a, int b){
    if(b == 0){
        return a;
    }else{
        return gcd(b, a%b);
    }
}

int lcm(int a, int b){
    return gcd(a, b)*(a/gcd(a, b))*(b/gcd(a,b));
}

int power(int a, int b){
    int multiple = 1;
    for(int c = 0; c<b; c++){
        multiple = multiple * a;
    }
    return multiple;
}
