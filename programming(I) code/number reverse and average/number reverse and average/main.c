//
//  main.c
//  number reverse and average
//
//  Created by 顏浩昀 on 2019/9/12.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>

int main() {
    int input = 0;
    float ReverseNum = 0;
    float sum = 0;
    float output = 0;
    int a = 0, b = 0, c = 0;
    scanf("%d", &input);
    a = input/100;
    b = (input%100)/10;
    c = (input%10);
    ReverseNum = c*100 + b*10 + a;
    sum = input + ReverseNum;
    output = sum/2;
    printf("%.1f", output);
    return 0;
}
