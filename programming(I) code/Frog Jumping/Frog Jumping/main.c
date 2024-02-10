//
//  main.c
//  Frog Jumping
//
//  Created by 顏浩昀 on 2019/11/23.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include<stdio.h>

int jump(int start, int end, int *count);
int store[26] = {0};
int energy[26] = {0};
int main(){
    int count = 0;
    int n = 0;
    int total = 0;
    scanf("%d", &n);
    for(int a = 0; a<n; a++){
        scanf("%d", &energy[a]);
    }
    total = jump(0, n-1, &count);
    printf("%d %d\n", total, count);
    return 0;
}

int jump(int start, int end, int *count){
    int delta_one = 0;
    int delta_two = 0;
    if(start == end)
        return 0;
    if((start+1) == end){
        delta_one = energy[end] - energy[start];
        if(delta_one < 0)
            delta_one = -delta_one;
        store[start] = delta_one;
        (*count) += 1;
        return store[start];
    }else{
        delta_one = energy[start+1] - energy[start];
        delta_two = energy[start+2] - energy[start];
        if(delta_one < 0)
            delta_one = -delta_one;
        if(delta_two < 0)
            delta_two = -delta_two;
        if(delta_one < delta_two){
            store[start] = jump(start+1, end, count) + delta_one;
            (*count) += 1;
        }else{
            store[start] = jump(start+2, end, count) + delta_two;
            (*count) += 1;
        }
        return store[start];
    }
}


