//
//  main.c
//  Launch of Collider
//
//  Created by 顏浩昀 on 2020/2/8.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>

int main() {
    int n = 0;
    int temp,min = 100000003;
    char direction[200500] = {'\0'};
    int position[200500] = {0};
    scanf("%d", &n);
    scanf("%s", direction);
    for(int i = 0; i < n; i++){
        scanf("%d", &position[i]);
    }
    for(int j = 0; j < n-1; j++){
        if((direction[j] == 'R') && (direction[j+1] == 'L')){
            temp = position[j+1] - position[j];
            j++;
            if(temp < min)
                min = temp;
        }
    }
    if(min == 100000003)
        printf("-1\n");
    else
        printf("%d\n", min/2);
    return 0;
}
