//
//  Machine and Engineer.cpp
//  Machine vs Engineer
//
//  Created by 顏浩昀 on 2020/5/20.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include "12762.h"
#include <cstring>

int min = -2147483647, max = 2147483646;

Engineer::Engineer(){
    this->init();
}

Engineer::~Engineer(){
    // TODO
}
void Engineer::init(){
    count = 0;
    for(int i = 0; i < 201; i++){
        value_history[i] = 0;
        action_history[i] = 0;
        answer_history[i] = -1;
    }
}

void Engineer::MakeQuery(char* query_str){
    // Interactive Version
    char op[100];
    int x;
    /*
    scanf("%s %d", op, &x);
    sprintf(query_str, "%s %d", op, x);
    */
    // Determine the query string by history
    // TODO
    if(count == 0){
        min = -2147483647; max = 2147483646;
        strcpy(op, "greater");
        x = 0;
        sprintf(query_str, "%s %d", op, x);
        action_history[count] = 1;
        value_history[count] = x;
    }
    else{
        if((max-min) == 0 ||(max-min) == 1){
            if(action_history[count-1] == 3){
                strcpy(op, "guess");
                x = max;
                sprintf(query_str, "%s %d", op, x);
                action_history[count] = 3;
                value_history[count] = x;
            }else{
                strcpy(op, "guess");
                x = min;
                sprintf(query_str, "%s %d", op, x);
                action_history[count] = 3;
                value_history[count] = x;
            }
        }
        else if(action_history[count-1] == 1){ //greater
            if(answer_history[count-1]){
                min = value_history[count-1];
                strcpy(op, "greater");
                x = (min+max)/2;
                sprintf(query_str, "%s %d", op, x);
                action_history[count] = 1;
                value_history[count] = x;
            }else{
                max = value_history[count-1];
                strcpy(op, "less");
                x = (min+max)/2;
                sprintf(query_str, "%s %d", op, x);
                action_history[count] = 2;
                value_history[count] = x;
            }
        }else if(action_history[count-1] == 2){ //less
            if(answer_history[count-1]){
                max = value_history[count-1];
                strcpy(op, "less");
                x = (min+max)/2;
                sprintf(query_str, "%s %d", op, x);
                action_history[count] = 2;
                value_history[count] = x;
            }else{
                min = value_history[count-1];
                strcpy(op, "greater");
                x = (min+max)/2;
                sprintf(query_str, "%s %d", op, x);
                action_history[count] = 1;
                value_history[count] = x;
            }
        }
    }
}
void Engineer::GetAnswer(bool ans){
    answer_history[count] = ans;
    count++;
}
