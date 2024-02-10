//
//  Stack.cpp
//  Stack
//
//  Created by 顏浩昀 on 2020/4/29.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include "10998.h"

List_stack::List_stack(){
    this->head = this->tail = NULL;
}

List_stack::~List_stack(){
}

void List_stack::push(const int &in){
    ListNode *cur = new ListNode(in);
    cur->prevPtr = this->tail;
    this->tail = cur;
}
void List_stack::pop(){
    if(this->tail == this->head){
        return;
    }else if(this->tail->prevPtr == this->head){
        free(this->tail);
        this->tail = this->head;
    }
    else{
        this->tail = this->tail->prevPtr;
        free(this->tail->nextPtr);
    }
}
void List_stack::print(){
    ListNode *tmp = this->tail;
    if(this->head == this->tail)    return;
    while (tmp->prevPtr != NULL) {
        std::cout<<tmp->data<<" ";
        tmp = tmp->prevPtr;
    }
    std::cout<<tmp->data;
}
