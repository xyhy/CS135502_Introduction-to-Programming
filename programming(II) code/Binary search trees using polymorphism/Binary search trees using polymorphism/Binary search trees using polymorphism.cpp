//
//  Binary search trees using polymorphism.cpp
//  Binary search trees using polymorphism
//
//  Created by 顏浩昀 on 2020/5/19.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include "11020.h"

Array_BST::Array_BST()
{
    for(int i = 0; i < 1025; i++){
        array[i] = 0;
    }
}

void Array_BST::insert(const int &key){
    int i = 1;
    int flag = search(key);
    while(!flag){
        if(array[i] == 0){
            array[i] = key;
            if(i >= pow(2, height()))   Height+=1;
            break;
        }else if(key < array[i]){
            i*=2;
            continue;
        }else if (key > array[i]){
            i = 2*i+1;
            continue;
        }
    }
}

bool Array_BST::search(const int &key) const{
    int i = 1;
    while(i < pow(2, height()) ){
        if(array[i] == key) return true;
        else if(array[i] > key){
            i*=2;
            continue;
        }else if(array[i] < key){
            i = 2*i +1;
            continue;
        }
    }
    return false;
}

List_BST::List_BST(){
}

void List_BST::insert(const int &key){
    int index = 1;
    ListNode* insertnode = createLeaf(key);
    ListNode* tmp = root;
    int flag = search(key);
    while(!flag){
        if(root == nullptr){
            root = insertnode;
            Height = height()+1;
            return;
        }
        if(key < tmp->key){
            if(tmp->left != nullptr){
                tmp = tmp->left;
                index*=2;
                continue;
            }
            else{
                tmp->left = insertnode;
                index*=2;
                if(index >= pow(2, height())){
                    Height = height()+1;
                }
                return;
            }
        }else if(key > tmp->key){
            if(tmp->right != nullptr){
                tmp = tmp->right;
                index = 2*index + 1;
            }
            else{
                tmp->right = insertnode;
                index = 2*index + 1;
                if(index >= pow(2,height())){
                    Height = height()+1;
                }
                return;
            }
        }
    }
}

bool List_BST::search(const int &key) const{
    ListNode *tmp = root;
    while(1){
        if(tmp == nullptr)  return false;
        if(tmp->key == key)    return true;
        else if(tmp->key < key){
            if(tmp->right != nullptr){
                tmp = tmp->right;
                continue;
            }
            else    return false;
        }else if(tmp->key > key){
            if(tmp->left != nullptr){
                tmp = tmp->left;
                continue;
            }
            else    return false;
        }
    }
}

ListNode* List_BST::createLeaf(int key)const{
    ListNode* newnode = new ListNode(key);
    return newnode;
}

void List_BST::deleteTree(ListNode *root){
    if(root->left != nullptr)   List_BST::deleteTree(root->left);
    if(root->right != nullptr)  List_BST::deleteTree(root->right);
    delete root;
}
