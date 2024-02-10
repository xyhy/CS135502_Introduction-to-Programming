//
//  Double Link List.cpp
//  Doubly Linked List
//
//  Created by 顏浩昀 on 2020/5/20.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include <stdexcept>
#include <cmath>
#include "12224.h"


void List::InsertHead(int data){
    ListNode *newhead = new ListNode(data);
    if(head == nullptr){
        middle = head = tail = newhead;
    }else{
        head->prev = newhead;
        newhead->next = head;
        head = newhead;
        if(!(getSize()%2))    middle = middle->prev;
    }
    cnt += 1;
    pos = floor(getSize()/2);
}

int List::RemoveHead(){
    int ans = 0;
    ListNode *tmp = head;
    if(head != nullptr){
        ans = head->data;
        if(head->next != nullptr){
            head = head->next;
            if(getSize()%2)   middle = middle->next;
        }
        else    middle = head = tail = nullptr;
        delete tmp;
    }else{
        throw std::out_of_range("fail");
    }
    cnt -= 1;
    pos = floor(getSize()/2);
    return ans;
}

void List::InsertTail(int data){
    ListNode *newtail = new ListNode(data);
    if(tail == nullptr){
        middle = tail = head = newtail;
    }else{
        tail->next = newtail;
        newtail->prev = tail;
        tail = newtail;
        if(getSize()%2)   middle = middle->next;
    }
    cnt += 1;
    pos = floor(getSize()/2);
}

int List::RemoveTail(){
    ListNode *tmp = tail;
    int ans = 0;
    if(tail != nullptr){
        ans = tail->data;
        if(tail->prev != nullptr){
            tail = tail->prev;
            if(!(getSize()%2))   middle = middle->prev;
        }
        else    middle = head = tail = nullptr;
        delete tmp;
    }else{
        throw std::out_of_range("fail");
    }
    cnt -= 1;
    pos = floor(getSize()/2);
    return ans;
}

void List::Swap(){
    if(head == nullptr)   return;
    ListNode *newhead = head;
    ListNode *newtail = tail;
    head->prev = tail;
    tail->next = head;
    middle->prev->next = nullptr;
    newtail = middle->prev;
    middle->prev = nullptr;
    newhead = middle;
    if(cnt%2)   middle = tail;
    else    middle = head;
    tail = newtail;
    head = newhead;
}

int List::getSize(){
    return cnt;
}

int List::getMiddle(){
    return pos;
}
