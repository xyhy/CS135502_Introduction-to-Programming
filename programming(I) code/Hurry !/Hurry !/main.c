//
//  main.c
//  Hurry !
//
//  Created by 顏浩昀 on 2020/1/7.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>

int min(int a, int b){
    return (a<b)?a:b; // return min distance
}
int main(){
    int t;
    int man, num;
    int used[3010] = {0};
    int l,L, r,R;
    int choose = 0;
    scanf("%d", &t);
    while(t--){
        scanf("%d %d", &num, &man);
        used[0] = 1;
        used[num+1] = 1;
        for(int x = 1; x<=num; x++)
            used[x] = 0;
        while(man--){
            int max_space = -1;
            for(int i = 1; i<=num; i++){
                L = 0;
                R = 0;
                l = i;
                r = i;
                if(used[i])
                    continue;
                while(!used[--l]){
                    L++;
                }
                while(!used[++r]){
                    R++;
                }
                if(min(L, R) > max_space){  //if min distance > max_distance -> choose it
                    max_space = min(L, R);
                    choose = i;
                }
            }
            used[choose] = 1;
        }
        printf("%d\n", choose);
    }
    return 0;
}
