//
//  GameStartScene.cpp
//  Mini Project 2(Tower Defense)
//
//  Created by 顏浩昀 on 2020/6/5.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "AudioHelper.hpp"
#include "GameEngine.hpp"
#include "Image.hpp"
#include "ImageButton.hpp"
#include "Label.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Resources.hpp"
#include "Slider.hpp"
#include "StageSelectScene.hpp"
#include "GameStartScene.hpp"


void GameStartScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 500, halfH * 7 / 4 - 50, 1000, 100);
    btn->SetOnClickCallback(std::bind(&GameStartScene::StartOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("CLICK TO START", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    bgmId = AudioHelper::PlayBGM("LNYX_Loose_Ends.wav");
}
void GameStartScene::Terminate() {
    AudioHelper::StopBGM(bgmId);
    IScene::Terminate();
}
void GameStartScene::StartOnClick(int stage) {
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
