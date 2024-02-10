//
//  main.c
//  Traveling Mail Carrier
//
//  Created by 顏浩昀 on 2019/12/8.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <limits.h>
int distance = 0;
int n = 0;
int min_distance = INT_MAX;
int visited[10] = {1};
int visted_num = 1;
int map[10][10];

void mail(int pos);

int main(){
    scanf("%d", &n);
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            scanf("%d", &map[i][j]);
        }
    }
    mail(0);
    printf("%d\n", min_distance);
    return 0;
}

void mail(int pos){
    if(visted_num == n){
        if((distance + map[pos][0]) < min_distance){
            min_distance = (distance + map[pos][0]);
        }
    }
    for(int i = 0; i<n; i++){
        if(!visited[i]){
            visited[i] = 1;
            visted_num++;
            distance += map[pos][i];
            mail(i);
            visited[i] = 0;
            visted_num--;
            distance -= map[pos][i];
        }
    }
}
