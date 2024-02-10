//
//  main.c
//  Little Brick's Dream
//
//  Created by 顏浩昀 on 2019/12/10.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>

int height[100000001];
int comfort_value[100000001];
int main() {
    int n,target;
    int j;
    int com = 0;
    scanf("%d %d", &n, &target);
    int ans[n];
    for(int i = 1; i<=n; i++){
        scanf("%d", &height[i]);
        for(j = i-1; j>0;){
            if(height[j] < height[i]){
                j = j-comfort_value[j]-1;
            }else{
                break;
            }
        }
        comfort_value[i] = i - j - 1;
        if(comfort_value[i] == target){
            ans[com++] = i;
        }
    }
    if(com > 0){
        printf("%d", ans[0]);
        for(int k = 1; k<com; k++){
            printf("%d", ans[k]);
        }
    }else{
        printf("ouo");
    }
    printf("\n");
    return 0;
}
