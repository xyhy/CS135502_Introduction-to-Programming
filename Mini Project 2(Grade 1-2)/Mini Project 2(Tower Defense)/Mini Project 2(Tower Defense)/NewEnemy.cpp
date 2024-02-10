//
//  NewEnemy.cpp
//  Mini Project 2(Tower Defense)
//
//  Created by 顏浩昀 on 2020/6/6.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <allegro5/base.h>
#include <random>
#include <string>

#include "NewEnemy.hpp"
#include "Point.hpp"
#include "PlayScene.hpp"

NewEnemy::NewEnemy(int x, int y) : Enemy("play/enemy-7.png", x, y, 15, 70, 30, 20) {
    if(speed < 400){
        speed += 50;
    }else{
        speed = 400;
    }
    // TODO 2 (6/8): You can imitate the 2 files: 'SoldierEnemy.hpp', 'SoldierEnemy.cpp' to create a new enemy.
}
