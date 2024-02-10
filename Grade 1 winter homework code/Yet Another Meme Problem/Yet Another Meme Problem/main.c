//
//  main.c
//  Yet Another Meme Problem
//
//  Created by 顏浩昀 on 2020/2/8.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>

int main() {
    int n = 0;
    scanf("%d", &n);
    while (n > 0) {
        long long int A, B;
        long long int multiple = 0;
        long long int pairs;
        scanf("%lld %lld", &A, &B);
        for(int i = 9; i <= B; i = i*10+9){
            multiple++;
        }
        pairs = A * multiple;
        printf("%lld\n", pairs);
        n--;
    }
    return 0;
}
