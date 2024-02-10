//
//  main.c
//  Bacteria Division
//
//  Created by 顏浩昀 on 2019/11/3.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>


long long int fast_pow(long long int a, long long int n);
int main(){
    long long int firstday = 0, multiple = 0, days = 0;
    while(scanf("%lld %lld %lld", &firstday, &multiple, &days) != EOF){
        long long int k = 0;
        k = firstday * fast_pow(multiple+1, days-1);
        printf("%lld\n", k%10177);
    }
    return 0;
}

long long int fast_pow(long long int a, long long int n){
    if(n == 0){
        return 1;
    }
    if(n == 1){
        return a;
    }
    else{
        long long int k = fast_pow(a, n/2);
        if(n%2 == 0){
            return (k*k)%10177;
        }else if(n%2 == 1){
            return (a*k*k)%10177;
        }
    }
    return 0;
}
