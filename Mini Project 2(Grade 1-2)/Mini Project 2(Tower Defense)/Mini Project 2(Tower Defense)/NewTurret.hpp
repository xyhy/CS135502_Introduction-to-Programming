//
//  NewTurret.hpp
//  Mini Project 2(Tower Defense)
//
//  Created by 顏浩昀 on 2020/6/6.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#ifndef NewTurret_hpp
#define NewTurret_hpp

#include "Turret.hpp"

class NewTurret: public Turret {
public:
    static const int Price;
    NewTurret(float x, float y);
    void CreateBullet() override;
};

#endif /* NewTurret_hpp */
