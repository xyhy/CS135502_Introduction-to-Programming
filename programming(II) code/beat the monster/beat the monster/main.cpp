//
//  main.cpp
//  beat the monster
//
//  Created by 顏浩昀 on 2020/6/19.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <queue>

struct state{
    int level;
    int hp;
    int enemy_hp;
    int step;
    state(int lv, int hp, int e_hp, int dist = 0) : level(lv), hp(hp), enemy_hp(e_hp), step(dist){}
};

bool map[20][305][405];

int main() {
    std::queue<state> move;
    int L, HP, MHP, MDMG;
    int dmg[20], health[20];
    std::cin>>L>>HP>>MHP>>MDMG;
    for(int i = 1; i <= L; i++){
        std::cin>>dmg[i]>>health[i];
    }
    move.push(state(1,HP,MHP));
    
    while (!move.empty()) {
        state now = move.front();
        if(now.enemy_hp <= 0)   break;
        move.pop();
        // really health
        int hl = now.hp+health[now.level];
        if(now.hp+health[now.level] > HP)   hl = HP;
        //level up
        if((now.level < L) && (now.hp > MDMG)){
            state next(now.level+1, now.hp-MDMG, now.enemy_hp, now.step+1);
            if(!map[next.level][next.hp][next.enemy_hp]){
                map[next.level][next.hp][next.enemy_hp] = true;
                move.push(next);
            }
        }
        //attack
        if((now.hp > MDMG) || (dmg[now.level] >= now.enemy_hp)){
            state next(now.level, now.hp-MDMG, now.enemy_hp-dmg[now.level], now.step+1);
            if(!map[next.level][next.hp][next.enemy_hp]){
                map[next.level][next.hp][next.enemy_hp] = true;
                move.push(next);
            }
        }
        //recover
        if((now.hp < HP) && (hl > MDMG)){
            state next(now.level, hl-MDMG, now.enemy_hp, now.step+1);
            if(!map[next.level][next.hp][next.enemy_hp]){
                map[next.level][next.hp][next.enemy_hp] = true;
                move.push(next);
            }
        }
    }
    if(move.empty())    std::cout<<"-1\n";
    else    std::cout<<move.front().step<<"\n";
    return 0;
}
