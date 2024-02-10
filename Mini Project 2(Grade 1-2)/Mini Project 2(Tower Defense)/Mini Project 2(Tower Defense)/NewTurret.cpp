//
//  NewTurret.cpp
//  Mini Project 2(Tower Defense)
//
//  Created by 顏浩昀 on 2020/6/6.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "NewBullet.hpp"
#include "Group.hpp"
#include "NewTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

const int NewTurret::Price = 150;
NewTurret::NewTurret(float x, float y) :
    // TODO 2 (2/8): You can imitate the 2 files: 'MachineGunTurret.hpp', 'MachineGunTurret.cpp' to create a new turret.
Turret("play/tower-base.png", "play/turret-5.png", x, y, 550, Price, 0.2) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void NewTurret::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new NewBullet(Position + normalized * 10 + normal * 15, diff, rotation, this));
    getPlayScene()->BulletGroup->AddNewObject(new NewBullet(Position + normalized * 10 - normal * 15, diff, rotation, this));
    getPlayScene()->BulletGroup->AddNewObject(new NewBullet(Position + normalized * 10 + normal * 45, diff, rotation, this));
    getPlayScene()->BulletGroup->AddNewObject(new NewBullet(Position + normalized * 10 - normal * 45, diff, rotation, this));
    AudioHelper::PlayAudio("missile.wav");
}
