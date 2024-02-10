//
//  main.c
//  Binary representation&sum
//
//  Created by 顏浩昀 on 2019/9/27.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>

int main() {
    int input = 0;
    int sum = 0;
    int times = 0;
    int addition = 0;
    int arr[11] = {0};
    int arr2[11] = {0};
    int bit = 0;
    scanf("%d", &input);
    sum = input + 1;
    for(int a = 1024; a >= 1; a = a/2){
        if((input / a) == 1){
            arr[times] = 1;
            input = input % a;
        }
        times+=1;
    }
    for(int b = 10; b > 0; b--){
        if(arr[b] == 1){
            addition+=1;
        } else{
            break;
        }
    }
    times = 0;
    for(int x = 1024; x >= 1; x = x/2){
        if((sum / x) == 1){
            arr2[times] = 1;
            sum = sum % x;
        }
        times+=1;
    }
    for(int c = 0; c < 11; c++){
        if(arr2[c] == 0){
            continue;
        } else{
            bit = c;
            break;
        }
    }
    for(; bit < 11; bit++){
        printf("%d", arr2[bit]);
    }
    printf(" %d", addition);
    return 0;
}
