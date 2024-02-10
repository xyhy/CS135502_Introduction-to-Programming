//
//  main.c
//  Hakka's Maze
//
//  Created by 顏浩昀 on 2019/12/10.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>

int visited[1001][1001] = {0};
int teleport = 0;
int n = 0, m = 0;

char map[1001][1001];

void go(int x, int y);
int main(){
    int t = 0;
    scanf("%d", &t);
    for(int k = 0; k<t; k++){
        scanf("%d %d", &n, &m);
        for(int i = 0; i<n; i++)
                scanf("%s", map[i]);
        memset(visited, 0, sizeof(visited));
        teleport = 0;
        go(0, 0);
        if(teleport){
            for(int i = 0; i<n; i++){
                for(int j = 0; j<m; j++){
                    if(map[i][j] == 'T')
                        go(i,j);
                }
            }
        }
        if(visited[n-1][m-1])
            printf("Yes\n");
        else
            printf("No\n");
    }
        return 0;
}

void go(int x, int y){
    if(visited[x][y])
        return ;
    visited[x][y] = 1;
    if(map[x][y] == 'T')
        teleport = 1;
    int dx[]={1,0,-1,0};
    int dy[]={0,-1,0,1};
    for(int i = 0; i<4; i++){
        int nextx = x+dx[i];
        int nexty = y+dy[i];
        if((nextx < 0) || (nexty < 0) || (nextx >= n) || (nexty >= m))
            continue;
        if(map[nextx][nexty] == '#')
            continue;
        go(nextx, nexty);
    }
}
