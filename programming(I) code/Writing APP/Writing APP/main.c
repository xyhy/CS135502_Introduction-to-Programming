//
//  main.c
//  Writing APP
//
//  Created by 顏浩昀 on 2019/11/11.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>
int check[1001][1001] = {0};
int del[1001][1001] = {0};
char str[1001];
int palindrome(int l, int r);
int main(){
    int n = 0, k = 0;
    scanf("%d %d", &n, &k);
    scanf("%s", str);
    if(palindrome(0, n-1) <= k)
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}

int palindrome(int l, int r){
    int ans;
    if(check[l][r])
        return del[l][r];
    if(l >= r){
        check[l][r] = 1;
        return 0;
    }
    if(str[l] == str[r]){
        ans = palindrome(l+1, r-1);
    }else{
        ans = (palindrome(l+1, r) < palindrome(l, r-1)) ?
            (1 + palindrome(l+1, r)) : (1 + palindrome(l, r-1));
    }
    check[l][r] = 1;
    del[l][r] = ans;
    return ans;
}
