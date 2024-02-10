//
//  main.c
//  Sentence Reversal
//
//  Created by 顏浩昀 on 2019/12/14.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

char ans_string[1000][1000];
char string[1000];
int k = 0;
void sentence_reversal(int i, int j);
int main(){
    while (fgets(string, 1000, stdin) != 0) {
        memset(ans_string, '\0', sizeof(ans_string));
        sentence_reversal(0, 0);
        memset(string, '\0', sizeof(string));
    }
    return 0;
}

void sentence_reversal(int i, int j){
    if(string[i] == '\0'){
        return;
    }else if(string[i] == ' '){
        k = 0;
        sentence_reversal(i+1, j+1);
        if(j != 0)
            printf(" %s", ans_string[j]);
        else
            printf(" %s\n", ans_string[j]);
    }else if(string[i] == '\n'){
        k = 0;
        sentence_reversal(i+1, j+1);
        if(j != 0)
            printf("%s", ans_string[j]);
        else
            printf("%s\n", ans_string[j]);
    }else{
        ans_string[j][k++] = string[i];
        sentence_reversal(i+1, j);
    }
}
