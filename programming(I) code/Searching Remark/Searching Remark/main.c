//
//  main.c
//  Searching Remark
//
//  Created by 顏浩昀 on 2019/12/17.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(){
    int i = 0;
    int total = 0;
    char sign[12] = {' ', '\n', '-', '/', ':', '(', ')', '[', ']', ',', '.'};
    char search[50];
    char input[1000];
    char *t;
    fgets(search, 50, stdin);
    for(i = 0; i<strlen(search); i++){
        search[i] = tolower(search[i]);
    }
    while (fgets(input, 1000, stdin) != 0){
        for(i = 0; i<strlen(input); i++){
            input[i] = tolower(input[i]);
        }
        t = strtok(input, sign);
        while(t != NULL){
            if(strlen(t) != strlen(search)-1){ //\n in search let its len add 1;
                t = strtok(NULL, sign);
                continue;
            }
            for(i = 0; i < strlen(search)-1; i++){
                if(t[i] != search[i]){
                    break;
                }
            }
            if(i == strlen(search)-1){
                total++;
            }
            t = strtok(NULL, sign);
        }
        //printf("%d\n", total);
    }
    printf("%d\n", total);
    return 0;
}
