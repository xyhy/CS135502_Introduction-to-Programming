//
//  main.cpp
//  Use std::set
//
//  Created by 顏浩昀 on 2020/6/4.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> in(){
    int i = 0;
    std::vector<int> int_seq;
    while(std::cin>>i){
        if(i == 0)  break;
        int_seq.push_back(i);
    }
    return int_seq;
}

void print(std::vector<int> out){
    for(int i = 0; i < out.size(); i++){
        std::cout<<out.at(i)<<' ' ;
    }
    std::cout<<"\n";
}

int value(std::vector<int> in){
    int value = 0;
    for(int i = 0; i < in.size(); i++){
        value += in.at(i)*(in.size()-i);
    }
    return value;
}

struct mycmp{
    bool operator()(const std::vector<int> &a, const std::vector<int> &b){
        return value(a) < value(b);
    }
};

int main() {
    std::set<std::vector<int>, mycmp> seq;
    std::string cmd;
    while(std::cin>>cmd){
        if(cmd == "insert"){
            std::vector<int> ins = in();
            std::set<std::vector<int>, mycmp>::iterator ite;
            for(ite = seq.begin(); ite != seq.end(); ite++){
                std::vector<int> cur = *ite;
                if(value(cur) == value(ins)){
                    std::cout<<"exist\n";
                    seq.erase(cur);
                    std::reverse(ins.begin(), ins.end());
                    break;
                }
            }
            seq.insert(ins);
        }else if(cmd == "range_out"){
            int from = value(in()), to = value(in());
            std::set<std::vector<int>, mycmp>::iterator ite;
            for(ite = seq.begin(); ite != seq.end(); ite++){
                std::vector<int> cur = *ite;
                if(value(cur) >= from && value(cur) <= to)  print(cur);
                else if(value(cur) > to)    break;
            }
        }else if(cmd == "output"){
            std::set<std::vector<int>, mycmp>::iterator ite;
            for(ite = seq.begin(); ite != seq.end(); ite++){
                //std::vector<int> cur = *ite;
                print(*ite);
            }
        }
    }
    
    return 0;
}
