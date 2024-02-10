//
//  main.c
//  String sorting
//
//  Created by 顏浩昀 on 2020/1/4.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
char string[200000][105];
int compare(const void* a,const void* b){
    const char *ia = (const char*) a;
    const char *ib = (const char*) b;
    return strcmp(ia, ib);
}
int main() {
    int count = 0;
    while((scanf("%s", string[count]) != EOF) && count<200000){
        count++;
    }
    qsort(string, count, sizeof(char)*105, compare);
    for(int i = 0; i<count; i++){
        printf("%s\n", string[i]);
    }
    return 0;
}
