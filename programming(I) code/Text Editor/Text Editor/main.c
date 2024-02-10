//
//  main.c
//  Text Editor
//
//  Created by 顏浩昀 on 2019/12/22.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>
char input[600];
char ans_text[600];
char now_input[600];
int main() {
    int cursor_pos = 0;
    fgets(input, 600, stdin);
    for(int i = 0; i<600; i++){
        if(input[i] == '/'){
            if(input[i+1] == 'b'){
                if(cursor_pos != 0){
                    strcpy(now_input, &ans_text[cursor_pos]);
                    cursor_pos--;
                    strcpy(&ans_text[cursor_pos], now_input);
                }
                i+=9;
                continue;
            }else if(input[i+1] == 'n'){
                i+=7;
                strcpy(now_input, &ans_text[cursor_pos]);
                strcpy(&ans_text[cursor_pos+1], now_input);
                ans_text[cursor_pos] = '\n';
                cursor_pos++;
                continue;
            }else if(input[i+1] == 'l'){
                if(cursor_pos != 0){
                    cursor_pos--;
                }
                i+=4;
                continue;
            }else if(input[i+1] == 'r'){
                if(ans_text[cursor_pos] != '\0'){
                    cursor_pos++;
                }
                i+=5;
                continue;
            }
        }else if(input[i] != '\n' && input[i] != '\0'){
            strcpy(now_input, &ans_text[cursor_pos]);
            strcpy(&ans_text[cursor_pos+1], now_input);
            ans_text[cursor_pos] = input[i];
            cursor_pos++;
        }
    }
    printf("%s", ans_text);
    return 0;
}
