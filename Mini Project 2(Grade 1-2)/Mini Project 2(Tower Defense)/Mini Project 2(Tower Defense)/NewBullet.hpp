//
//  NewBullet.hpp
//  Mini Project 2(Tower Defense)
//
//  Created by 顏浩昀 on 2020/6/6.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#ifndef NewBullet_hpp
#define NewBullet_hpp

#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class NewBullet : public Bullet {
public:
    explicit NewBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
    void OnExplode(Enemy* enemy) override;
};

#endif /* NewBullet_hpp */
