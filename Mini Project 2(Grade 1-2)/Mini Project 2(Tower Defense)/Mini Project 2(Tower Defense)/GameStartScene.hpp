//
//  GameStartScene.hpp
//  Mini Project 2(Tower Defense)
//
//  Created by 顏浩昀 on 2020/6/5.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#ifndef GameStartScene_hpp
#define GameStartScene_hpp

#include <allegro5/allegro_audio.h>
#include <memory>
#include "IScene.hpp"

class GameStartScene final : public Engine::IScene {
private:
    ALLEGRO_SAMPLE_ID bgmId;
public:
    explicit GameStartScene() = default;
    void Initialize() override;
    void Terminate() override;
    void StartOnClick(int stage);
};

#endif /* GameStartScene_hpp */
