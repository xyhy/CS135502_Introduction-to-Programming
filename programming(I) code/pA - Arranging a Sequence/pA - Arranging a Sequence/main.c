//
//  main.c
//  pA - Arranging a Sequence
//
//  Created by 顏浩昀 on 2019/10/18.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>

int main() {
    int num = 0, times = 0;
    int output[200001] = {0};
    int tmp [200001] = {0};
    scanf("%d %d", &num, &times);
    int arr[times];
    while(times > 0){
        scanf("%d", &arr[times-1]);
        times--;
    }
    for(int a = 0; a<times; a++){
        if(arr[a] != -1){
            for(int b = a+1; b<times; b++){
                if(arr[a] == arr[b]){
                    arr[b] = -1;
                }
            }
        }
    }
    printf("%d%d%d", arr[0], arr[1],arr[2]);
    for(int a = 0; a < times; a++){
        for(int b = 0; b < times; b++){
            if(arr[b] != -1){
                output[a] = arr[b];
                break;
            }
        }
    }
    return 0;
}
