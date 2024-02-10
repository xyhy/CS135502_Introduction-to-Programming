//
//  main.c
//  Low Wage
//
//  Created by 顏浩昀 on 2019/9/26.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>

int main(){
    int HourWage = 0;
    int starthr, startmin, startsec;
    int endhr, endmin, endsec;
    int workhr, workmin, worksec;
    char a,b,c,d,e;
    scanf("%d", &HourWage);
    scanf("%d%c%d%c%d %c %d%c%d%c%d", &starthr, &a, &startmin, &b, &startsec, &c, &endhr, &d, &endmin, &e, &endsec);
    workhr = endhr - starthr;
    workmin = endmin - startmin;
    worksec = endsec - startsec;
    if(worksec < 0){
        worksec += 60;
        workmin -= 1;
    }
    if(workmin < 0){
        workmin += 60;
        workhr -= 1;
    }
    printf("Working Time: %d Hour(s) %d Minute(s) %d Second(s)\n", workhr, workmin, worksec);
    printf("Daily Wage: %d TWD\n", workhr*HourWage);
    return 0;
}
