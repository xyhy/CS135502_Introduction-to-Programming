//
//  main.cpp
//  Looking for Chinese Tutor
//
//  Created by 顏浩昀 on 2020/6/19.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include <map>
#include <string>

std::map<std::string, std::string> pokemon{
    {"Wa","Waninoko"}, {"Mi","Milotic"}, {"Ma","Magikarp"}, {"Va","Vaporeon"}, {"Sh","Sharpedo"},{"Tapu","Tapu Fini"}, {"Em","Empoleon"}, {"La","Lapras"}, {"Pi","Pikachu"}, {"Pe","Pikachu"}, {"Me","Mega Gyarados"},
};

int main() {
    int T;
    std::cin>>T;
    while (T--) {
        std::string school, name;
        std::cin>>name>>school;
        bool tutor = false;
        for(auto i : pokemon){
            if(name.substr(0, i.first.size()) == i.first){
                tutor = true;
                std::cout<<name<<" the "<<school<<" "<<i.second<<"\n";
                break;
            }
        }
        if(!tutor)  std::cout<<name<<" is looking for a Chinese tutor, too!\n";
    }
    return 0;
}
