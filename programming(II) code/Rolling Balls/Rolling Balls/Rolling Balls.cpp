//
//  Rolling Balls.cpp
//  Rolling Balls
//
//  Created by 顏浩昀 on 2020/6/5.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include<iostream>
#include<string>
#include<sstream>
#include<cmath>
#include "12793.h"
using namespace std;

void freetree(Node* root){
    if(root == nullptr) return;
    if(root->left != nullptr)   freetree(root->left);
    if(root->right != nullptr)  freetree(root->right);
    free(root);
}

MultiSet_Tree::MultiSet_Tree(){
    root = nullptr;
}
MultiSet_Tree::~MultiSet_Tree(){
    freetree(root);
}
void MultiSet_Tree::Insert(const Color& newone){
    Node* newnode = new Node;
    newnode->key = newone;
    newnode->left = newnode->right = nullptr;
    if(root == nullptr) root = newnode;
    else{
        root->right = newnode;
        newnode->left = root;
        root = newnode;
    }
}
void MultiSet_Tree::Delete(const Color& overone){
    Node *tmp = root;
    if(Search(overone) == 0)    return;
    else{
        while(!(root->key == overone)) root = root->left;
        root->left->right = root->right;
        root->right->left = root->left;
        delete root;
        root = tmp;
    }
}
const int MultiSet_Tree::Search(const Color& trace) const{
    int cnt = 0;
    Node *tmp = root;
    while(tmp != nullptr){
        if(trace == tmp->key)   cnt++;
        tmp = tmp->left;
    }
    return cnt;
}

Node::Node(){
    key = Color();
    value = 1;
    left = right = nullptr;
}

Node::~Node(){
}


bool Color::operator < (const Color& other) const{
    if(r<other.r)   return true;
    else if(r > other.r)    return false;
    else{
        if(g<other.g)   return true;
        else if(g > other.g)    return false;
        else{
            if(b<other.b)   return true;
            else    return false;
        }
    }
}

bool Color::operator > (const Color& other) const{
    if(r>other.r)   return true;
    else if(r < other.r)    return false;
    else{
        if(g>other.g)   return true;
        else if(g < other.g)    return false;
        else{
            if(b>other.b)   return true;
            else    return false;
        }
    }
}
bool Color::operator == (const Color& other) const{
    if(r==other.r && g==other.g && b==other.b)  return true;
    else    return false;
}
Color& Color::operator = (const Color& other){
    this->b = other.b;
    this->r = other.r;
    this->g = other.g;
    return *this;
}
