//
//  String Operation.cpp
//  String Operation
//
//  Created by 顏浩昀 on 2020/5/14.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include "11417.h"

Str::Str(char* c):head(nullptr), tail(nullptr)
{
    int i = 0;
    while(c[i] != '\0'){
        Char *tmp = new Char(c[i]);
        if(i == 0){
            this->head = tmp;
            this->tail = tmp;
            i++;
        }else{
            this->tail->next = tmp;
            this->tail = tmp;
            i++;
        }
    }
}

Str::Str(const Str& str){
    this->head = new Char(str.head->text);
    this->tail = this->head;
    Char *tmp = str.head->next;
    while (tmp) {
        Char *new_char = new Char(tmp->text);
        this->tail->next = new_char;
        this->tail = new_char;
        tmp = tmp->next;
    }
}

Str& Str::strInsert(const Str& insert){
    Str *tmp = new Str(insert);
    this->tail->next = tmp->head;
    this->tail = tmp->tail;
    //delete tmp;
    return *this;
}

