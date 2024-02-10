//
//  main.c
//  Light Reflection
//
//  Created by 顏浩昀 on 2019/11/28.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>

int main(){
    int direction = 1;
    int frequency;
    int t = 1;
    int x_axis, y_axis;
    int x, y;
    scanf("%d %d", &x_axis, &y_axis);
    scanf("%d %d", &x, &y);
    scanf("%d", &frequency);
    for(; t < frequency; t++){
        if(((x == 1) || (x == x_axis)) && ((y == 1) || (y == y_axis)))
            break;
        if(direction == 1){
            while(1){
                x--;
                y++;
                if(x == 1){
                    direction = 2;
                    break;
                }else if(y == y_axis){
                    direction = 4;
                    break;
                }
            }
        }else if(direction == 2){
            while (1) {
                x++;
                y++;
                if(y == y_axis){
                    direction = 3;
                    break;
                }else if(x == x_axis){
                    direction = 1;
                    break;
                }
            }
        }else if(direction == 3){
            while (1) {
                x++;
                y--;
                if(x == x_axis){
                    direction = 4;
                    break;
                }else if(y == 1){
                    direction = 2;
                    break;
                }
            }
        }else if(direction == 4){
            while (1) {
                x--;
                y--;
                if(y == 1){
                    direction = 1;
                    break;
                }else if (x == 1){
                    direction = 3;
                    break;
                }
            }
        }
    }
    printf("(%d,%d)", x, y);
    return 0;
}

