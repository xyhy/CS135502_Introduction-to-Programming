//
//  main.c
//  Rebranding
//
//  Created by 顏浩昀 on 2020/2/13.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>

char alpha[30] = {'\0'};
int idx[30] = {0};

void swap_alpha(char *x, char *y){
    char temp = *x;
    *x = *y;
    *y = temp;
    return;
}
void swap_idx(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
    return;
}

int main() {
    int str_num = 0, rep_time = 0;
    char str[200005] = {'\0'};
    scanf("%d %d", &str_num, &rep_time);
    scanf("%s", str);
    for(int i = 0; i < 26; i++){
        idx[i] = i;
        alpha[i] = (char)('a' + i);
    }
    while (rep_time--){
        char x, y;
        scanf(" %c %c", &x, &y);
        swap_alpha(&alpha[idx[x-'a']], &alpha[idx[y-'a']]);
        swap_idx(&idx[x-'a'], &idx[y-'a']);
    }
    for(int j = 0; j < str_num; j++){
        printf("%c",alpha[str[j] - 'a']);
    }
    printf("\n");
    return 0;
}
