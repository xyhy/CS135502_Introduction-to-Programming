//
//  main.c
//  pE - Exquisite Substrings
//
//  Created by 顏浩昀 on 2019/10/24.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <string.h>

int exquisite(char s[], int a, int b);
int store[2001][2001] = {0};
int main() {
    char string [2001];
    int len = 0;
    while(scanf("%s", string) != EOF){
        int sum = 0;
        len = strlen(string);
        
    }
    return 0;
}

int exquisite(char s[], int a, int b){
    if(a >= b){
        return 0;
    }else{
        if(s[a] == s[b]){
            return exquisite(s, a+1, b-1);
        }else{
            return 1;
        }
    }
}

