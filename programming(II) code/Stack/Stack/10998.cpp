//
//  main.cpp
//  Stack
//
//  Created by 顏浩昀 on 2020/4/28.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include<iostream>
#include<string.h>
#include "10998.h"
using namespace std;

int main(){
    List_stack L_stack;
    char command[10];
    int n;
    while(cin>>command){

        if(strcmp(command,"pop")==0){
            L_stack.pop();
        }else if(strcmp(command,"push")==0){
            cin >> n;
            L_stack.push(n);
        }else if(strcmp(command, "print") == 0){
            L_stack.print();
            cout << endl;
        }
    }
    return 0;
}
