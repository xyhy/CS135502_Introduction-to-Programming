//
//  main.c
//  OuQ String
//
//  Created by 顏浩昀 on 2020/2/7.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>

char Sn[1000000000];
long long int a = 0;
long long int l = 0, r = 0;
void OuQ_list(int level){
    if(level == 0){
        return;
    }else{
        Sn[a++] = 'O';
        OuQ_list(level-1);
        Sn[a++] = 'u';
        OuQ_list(level-1);
        Sn[a++] = 'Q';
        return;
    }
}

int main() {
    int n = 0;
    while (scanf("%d %lld %lld", &n, &l, &r) != EOF) {
        OuQ_list(n);
        for(long long int i = l; i <= r; i++){
            printf("%c", Sn[i]);
        }
        a = 0;
    }
    return 0;
}
