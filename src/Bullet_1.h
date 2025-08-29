#pragma once
#include"Bullet.h"
class Bullet_1 :
    public Bullet
{
public:
    Bullet_1(int startX, int startY, int bulletDamage, int bulletVelocity, int vx, int vy);
    Bullet_1();
};