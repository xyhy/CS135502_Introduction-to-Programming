//
//  Base64 Encoding.cpp
//  Base64 Encoding
//
//  Created by 顏浩昀 on 2020/6/4.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "12787.h"


void Base64Codec::encode(){
    std::stringstream s;
    int each_8_bits[20000] = {0};
    int len = code_str.length();
    int num, remain, comp;
    if(len*8%6 == 0){
        num = len*8/6;
        remain = 0;
        comp = 0;
    }
    else{
        num = len*8/6+1;
        remain = len*8%6;
        comp = (6-remain)/2;
    }
    //printf("num : %d remain : %d comp : %d\n", num, remain, comp);
    for(int i = 0 ; i < len; i++){
        int ans = (int)(code_str[i] - 0);
        for(int j = i*8+7; j>=i*8; j--){
            each_8_bits[j] = ans%2;
            ans /= 2;
            //printf("each_8_bit[%d] : %d\n", j, each_8_bits[j]);
            if(ans == 0)    break;
        }
    }
    for(int i = 0; i < num; i++){
        int ret = 0;
        for(int j = i*6; j < i*6+6; j++){
            ret += each_8_bits[j] * (pow(2,5-(j%6)));
        }
        //printf("ret : %d\n", ret);
        s<<encodeCharacter(ret);
    }
    while (comp--) {
        s<<'=';
    }
    
    code_str = s.str();
}
