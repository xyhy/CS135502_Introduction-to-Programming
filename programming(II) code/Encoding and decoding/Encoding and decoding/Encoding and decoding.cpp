//
//  Encoding and decoding.cpp
//  Encoding and decoding
//
//  Created by 顏浩昀 on 2020/5/19.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include "11014.h"
void RleCodec::encode(){
    std::stringstream output;
    unsigned long len = code_str.length();
    if(len == 1)    output<<code_str[0];
    int count = 1;
    for(int i = 1; i < len; i++){
        if(code_str[i] == code_str[i-1]){
            count++;
            if(i == len-1){
                if(count == 2)  output<<code_str[i]<<code_str[i];
                else    output<<count<<code_str[i];
            }
        }else if((code_str[i] != code_str[i-1]) && (count==1)){
            output<<code_str[i-1];
            if(i == len-1){
                output<<code_str[i];
            }
        }else if ((code_str[i] != code_str[i-1]) && (count==2)){
            output<<code_str[i-1]<<code_str[i-1];
            count = 1;
            if(i == len-1){
                output<<code_str[i];
            }
        }else if((code_str[i] != code_str[i-1]) && (count>2)){
            output<<count<<code_str[i-1];
            count = 1;
            if(i == len-1){
                output<<code_str[i];
            }
        }
    }
    code_str = output.str();
    encoded = true;
}

void RleCodec::decode(){
    std::stringstream output;
    unsigned long len = code_str.length();
    //std::cout<<len<<"\n";
    int count = 0;
    for(int i = 0; i<len; i++){
        if(isdigit(code_str[i])){
            count*= 10;
            count+= (code_str[i] - '0');
            //std::cout<<"count: "<<count<<"\n";
        }else{
            if(count > 0){
                while(count--){
                    output<<code_str[i];
                    //std::cout<<"count after put into output: "<<count<<"\n";
                }
                count = 0;
            }else{
                output<<code_str[i];
            }
        }
    }
    code_str = output.str();
    encoded = false;
}

