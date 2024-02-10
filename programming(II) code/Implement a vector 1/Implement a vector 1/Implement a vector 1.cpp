//
//  Implement a vector 1.cpp
//  Implement a vector 1
//
//  Created by 顏浩昀 on 2020/5/15.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include<iostream>
#include<string>
#include"11420.h"
#include<cstddef>
#include<iosfwd>
#ifdef ONLINE_JUDGE
#include"NTHUOJLock"
#endif

void oj::Vector::pop_back(){
    if(this->size() > 0)  this->last_ = this->last_ - 1;
}

void oj::Vector::push_back(value_type val){
    if(this->size() >= this->capacity()){
        size_type new_capacity = ((this->capacity())*3 > (this->capacity())+1) ? (this->capacity())*3 : (this->capacity())+1;
        reserve(new_capacity);
    }
    *(this->last_) = val;
    this->last_ = this->last_+1;
}

void oj::Vector::reserve(size_type new_capacity){
    if(new_capacity > this->capacity()){
        pointer begin2 = new value_type[new_capacity];
        for(Int i = 0; i < this->size(); i++){
            begin2[i] = this->begin_[i];
        }
        size_type ori_size = this->size();
        delete [] this->begin_;
        this->begin_ = begin2;
        this->end_ = begin_ + new_capacity;
        this->last_ = begin_ + ori_size;
    }
}

oj::Vector::~Vector(){
    delete [] begin_;
}
