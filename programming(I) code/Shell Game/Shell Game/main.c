//
//  main.c
//  Shell Game
//
//  Created by 顏浩昀 on 2019/9/26.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>

int main() {
    int N = 0;
    int swap1, swap2, swap3;
    int swap[5] = {0,1,2,3,4};
    scanf("%d", &N);
    for(int a = 0; a < N; a++){
        scanf("%d%d", &swap1, &swap2);
        swap3 = swap[swap1];
        swap[swap1] = swap[swap2];
        swap[swap2] = swap3;
    }
    printf("%d %d %d %d %d", swap[0],swap[1],swap[2],swap[3],swap[4]);
    return 0;
}
