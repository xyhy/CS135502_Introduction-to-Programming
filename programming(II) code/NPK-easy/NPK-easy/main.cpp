//
//  main.cpp
//  NPK-easy
//
//  Created by 顏浩昀 on 2020/6/18.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <algorithm>

int main() {
    std::list<int> line;
    std::queue<int> country[3];
    int T;
    std::string cmd;
    std::cin>>T;
    while(T--){
        std::cin>>cmd;
        int id;
        if(cmd == "ENQUEUE"){
            int num;
            std::cin>>id;
            num = id%3;
            country[num].push(id);
            if(find(line.begin(), line.end(), num) == line.end()){
                line.push_back(num);
            }
        }else if(cmd == "DEQUEUE"){
            int num = line.front();
            std::cout<<country[num].front()<<"\n";
            country[num].pop();
            if(country[num].empty())    line.pop_front();
        }
    }
    return 0;
}
