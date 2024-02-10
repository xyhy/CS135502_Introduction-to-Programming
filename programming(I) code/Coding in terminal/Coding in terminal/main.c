//
//  main.c
//  Coding in terminal
//
//  Created by 顏浩昀 on 2020/1/7.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <string.h>

char input[1000000];
char terminal[1000000];
char temp[100000];
int main() {
    //declaration
    int j= 0;
    int line_initial = 0;
    int max_words_num = 0, max_line_num = 0;
    int a = 0,b = 0;
    int x,y;
    int cursor = 0;
    //input
    fgets(input, 1000000, stdin);
    for(int i = 0; i < strlen(input); i++){
        //read special character
        if(input[i] == '\\'){
            // TODO : newline
            if(input[i+1] == 'n'){
                i++;
                strcpy(temp, &terminal[cursor]);
                terminal[cursor] = '\n';
                strcpy(&terminal[cursor+1], temp);
                cursor++;
            //TODO : backspace
            }else if(input[i+1] == 'b'){
                i++;
                if(cursor != 0){
                    strcpy(temp, &terminal[cursor]);
                    cursor--;
                    strcpy(&terminal[cursor], temp);
                }
            //TODO : cursor left
            }else if(input[i+1] == 'l'){
                i++;
                if(cursor != 0){
                    cursor--;
                }
            // TODO : cursor right
            }else if(input[i+1] == 'r'){
                i++;
                if(terminal[cursor] != '\0'){
                    cursor++;
                }
            // TODO : set display size
            }else if(input[i+1] == 's'){
                max_words_num = 0;
                max_line_num = 0;
                x = i + 4;
                while(input[x] != ' '){
                    b *= 10;
                    a = (int)(input[x] - '0');
                    b += a;
                    x++;
                }
                max_words_num = b;
                a = 0;
                b = 0;
                y = x + 1;
                while(input[y] != ']'){
                    b *= 10;
                    a = (int)(input[y] - '0');
                    b += a;
                    y++;
                }
                max_line_num = b;
                a = 0;
                b = 0;
                i += (y-i);
            }
        //read normal character
        }else if(input[i] != '\n' && input[i] != '\0'){
            strcpy(temp, &terminal[cursor]);
            terminal[cursor] = input[i];
            strcpy(&terminal[cursor+1], temp);
            cursor++;
        }
    }
    //printf("%d %d", max_words_num, max_line_num);
    // output
    while(j<strlen(terminal) && max_line_num){
        //if read newline do it.
        if(terminal[j] == '\n'){
            max_line_num--;
            if(max_line_num){
                line_initial = j+1;
                printf("%c", terminal[j]);
                j++;
            }
        }else{
            //check size is ok and output
            if((j-line_initial) < max_words_num){
                printf("%c", terminal[j]);
                j++;
            }else{
                //oversize. do newline and then output
                max_line_num--;
                if(max_line_num){
                    printf("\n");
                    line_initial = j;
                    printf("%c", terminal[j]);
                    j++;
                }
            }
        }
    }
    return 0;
}

