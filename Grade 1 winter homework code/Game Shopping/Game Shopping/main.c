//
//  main.c
//  Game Shopping
//
//  Created by 顏浩昀 on 2020/2/10.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>

int main() {
    int game_value[1050] = {0};
    int wallet[1050] = {0};
    int g = 0, w = 0;
    int can_buy = 0;
    int j = 0, k = 0;
    scanf("%d %d", &g, &w);
    for(int i = 0; i < g; i++){
        scanf("%d", &game_value[i]);
    }
    for(int i = 0; i < w; i++){
        scanf("%d", &wallet[i]);
    }
    while(j < g && k < w){
        if(wallet[k] >= game_value[j]){
            can_buy++;
            k++;
            j++;
        }else{
            j++;
        }
    }
    printf("%d\n", can_buy);
    return 0;
}
