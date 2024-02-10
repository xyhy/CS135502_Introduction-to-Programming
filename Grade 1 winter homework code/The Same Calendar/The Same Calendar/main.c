//
//  main.c
//  The Same Calendar
//
//  Created by 顏浩昀 on 2020/2/8.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include<stdio.h>

int is_leap_year(int year){
    if(year%4 != 0){
        return 0;
    }else if(year%4 == 0 && year%100 != 0){
        return 1;
    }else if(year%100 == 0 && year%400 != 0){
        return 0;
    }else{
        return 1;
    }
}
int main(){
    int n;
    int year;
    scanf("%d", &n);
    while(n--){
        scanf("%d", &year);
        int ori_year = is_leap_year(year);
        int shift = 0;
        shift += (ori_year) ? 2 : 1;
        year++;
        while(shift != 0 || ori_year != is_leap_year(year)){
            if(is_leap_year(year)){
                shift += 2;
            }else{
                shift += 1;
            }
            shift = shift%7;
            year++;
        }
        printf("%d\n", year);
    }
}
