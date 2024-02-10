//
//  main.c
//  Mexican Wave
//
//  Created by 顏浩昀 on 2019/10/4.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>

int main() {
    int T, m, n, t;
    scanf("%d", &T);
    for(int i = 0; i < T; i++){
    scanf("%d%d%d", &m, &n, &t);
    if(((t - n) > m)){
        for(int a = 0; a < m; a++){
            printf("-");
        }
    }else if((t - n) <= 0){
        for(int a = 0; a < t; a++){
            printf("^");
        }
        for(int b = 0; b <(m - t); b++){
            printf("-");
        }
    }else{
        for(int a = 0; a <(t - n); a++){
            printf("-");
        }
        if((m -(t - n)) <= n){
            for(int b = 0; b <(m - (t - n)); b++){
                printf("^");
            }
        }else{
            for(int b = 0; b < n; b++){
                printf("^");
            }
            for(int c = 0; c <(m -t); c++){
                printf("-");
            }
        }
    }
        printf("\n");
    }
    return 0;
}
