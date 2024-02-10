//
//  main.c
//  Happy New Year
//
//  Created by 顏浩昀 on 2020/2/7.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>

int main() {
    int n = 0;
    int max, min;
    int total;
    scanf("%d", &n);
    int arr[n+1];
    for (int i = 0; i <= n; i++) {
        scanf("%d", &arr[i]);
    }
    max = min = arr[0];
    for(int i = 1; i <=n; i++){
        if(arr[i] > max)
            max = arr[i];
        if(arr[i] < min)
            min = arr[i];
    }
    total = 2*((max - arr[0]) + (arr[0] - min));
    printf("%d\n", total);
}
