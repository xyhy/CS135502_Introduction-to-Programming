//
//  main.c
//  Palindrome
//
//  Created by 顏浩昀 on 2019/10/12.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <string.h>

int compare(char s[],int a, int b);
int main() {
    char input[1000000];
    while(scanf("%s", input) != EOF){
        if(compare(input, 0, strlen(input)-1 ) == 1){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}

int compare(char s[],int a, int b){
    if(a >= b){
        return 1;
    }else{
        if(s[a] == s[b]){
            return compare(s, a+1, b-1);
        }else{
            return 0;
        }
    }
}
