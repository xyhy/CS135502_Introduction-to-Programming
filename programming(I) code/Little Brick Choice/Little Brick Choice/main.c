//
//  main.c
//  Little Brick Choice
//
//  Created by 顏浩昀 on 2019/11/19.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include<stdio.h>
#include<string.h>

int len = 0;
char arr[17] = {'\0'};
char ans_arr[17] = {'\0'};
int flag = 0;
void swap(int a, int b);
void perm(int pos);
int main(){
    scanf("%s", arr);
    len = strlen(arr);
    for(int a = 0; a<len; a++){
        for(int b = a+1; b<len; b++){
            if(arr[a] > arr[b])
                swap(a, b);
        }
    }
    perm(0);
    printf("\n");
    return 0;
}
void swap(int a, int b){
    char tmp;
    tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}
void perm(int pos){
    if(pos >= 4){
        ans_arr[pos] = '\0';
        if(flag == 0){
            printf("%s", ans_arr);
            flag = 1;
        }else
            printf(", %s", ans_arr);
    }
    for(int place = 0; place < len; place++){
        if(arr[place] > ans_arr[pos-1]){
            ans_arr[pos] = arr[place];
            perm(pos+1);
        }
    }
}
