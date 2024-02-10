//
//  main.c
//  Queries on a String
//
//  Created by 顏浩昀 on 2020/3/2.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <string.h>

int main() {
    char s[10050];
    char str_copy[10050] = {'\0'};
    char str_shift[10050] = {'\0'};
    int time = 0;
    int left, right, shift;
    scanf("%s", s);
    scanf(" %d", &time);
    while (time--) {
        scanf(" %d %d %d", &left, &right, &shift);
        shift = shift%(right - left + 1);
        strncpy(str_copy, &s[left-1], right-left+1);
        strcpy(str_shift, &str_copy[right-left+1-shift]);
        strncpy(&str_shift[shift], str_copy, right-left+1-shift);
        strncpy(&s[left-1], str_shift, right-left+1);
    }
   printf("%s\n", s);
    return 0;
}
