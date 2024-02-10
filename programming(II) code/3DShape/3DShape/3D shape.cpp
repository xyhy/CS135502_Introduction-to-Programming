//
//  3D shape.cpp
//  3DShape
//
//  Created by 顏浩昀 on 2020/5/15.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include "11443.h"

oj::Sphere::Sphere(double r, double pi) :radius(r), pi(pi)
{
    if(radius<0 || pi<0)    setVolume(0);
    else    setVolume(4.0/3.0 * pi * radius*radius*radius);
}
oj::Cone::Cone(double r, double h, double pi)   :radius(r), height(h), pi(pi)
{
    if(radius<0 || height<0 || pi<0)    setVolume(0);
    else    setVolume(1.0/3.0 * pi * radius*radius * height);
}
oj::Cuboid::Cuboid(double l, double w, double h)   :length(l), width(w), height(h)
{
    if(length<0 || width<0 || height<0) setVolume(0);
    else    setVolume(length * width * height);
}
oj::Cube::Cube(double a) : Cuboid(a, a, a)
{
}
