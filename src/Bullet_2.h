#pragma once
#include"Bullet.h"
class Bullet_2 :
    public Bullet
{
public:
    Bullet_2(int startX, int startY, int bulletDamage, int bulletVelocity, double vx, double vy);
    Bullet_2();
};