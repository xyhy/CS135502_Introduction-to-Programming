//
//  Use std::map.cpp
//  Use std::map
//
//  Created by 顏浩昀 on 2020/6/4.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include <set>
#include "11447.h"

namespace oj {
    void insert(std::map<int,String> &ma,int key,const std::string &str){
        auto tmp = ma.find(key);
        std::string str2;
        if(tmp != ma.end()){
            str2 = str + tmp->second.str;
            ma.erase(tmp);
        }else{
            str2 = str;
        }
        ma.insert(std::pair<int,String>(key, String(str2)));
    }
    void output(const std::map<int,String> &ma,int begin,int end){
        for(auto &t : ma){
            if(t.first>=begin && t.first<=end){
                std::cout<<t.second<<' ';
            }
        }
    }
    void erase(std::map<int,String> &ma,int begin,int end){
        std::set<int> del;
        for(auto &t : ma){
            if(t.first>=begin && t.first<=end){
                del.insert(t.first);
            }
        }
        for(auto key : del){
            ma.erase(key);
        }
    }

    std::ostream& operator<<(std::ostream &os,const std::map<int,String> &ma){
        for(auto &t : ma){
            os<<t.second<<' ';
        }
        return os;
    }
}
