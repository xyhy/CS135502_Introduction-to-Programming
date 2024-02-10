//
//  main.cpp
//  Count the Leaves
//
//  Created by 顏浩昀 on 2020/6/18.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include <set>

int main() {
    int test;
    while (std::cin>>test) {
        std::set<int> total;
        std::set<int> parent;
        if(test == 0)   break;
        while(test--){
            int left, right;
            std::cin>>left>>right;
            total.insert(left);
            total.insert(right);
            parent.insert(left);
        }
        int root;
        std::cin>>root;
        std::cout<<total.size() - parent.size()<<"\n";
    }
    return 0;
}
