//
//  Only children make choice.cpp
//  Only children make choice
//
//  Created by 顏浩昀 on 2020/5/20.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include "12257.h"

Animal::Animal(Zoo *zoo, string name)   :species(name), belong(zoo)
{
    this->belong->born(species);
}

Dog::Dog(Zoo *zoo) : Animal(zoo, "Dog")
{
    
}

Dog::~Dog(){
    
}

Cat::Cat(Zoo *zoo) : Animal(zoo, "Cat")
{
    
}

Cat::~Cat(){
    
}

Caog::Caog(Zoo *zoo) : Dog(zoo), Cat(zoo), Animal(zoo, "Caog")
{
    
}

Caog::~Caog(){
    
}

void Caog::barking(){
    std::cout<<"woof!woof!meow!\n";
}

void Caog::throwBall(){
    std::cout<<"it looks happy!\n";
}

void Caog::carton(){
    std::cout<<"it looks so happy!\n";
}
