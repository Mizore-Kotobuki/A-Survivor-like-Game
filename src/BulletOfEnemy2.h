#pragma once
#include"Bullet.h"
class BulletOfEnemy2 :
    public Bullet
{
public:
    BulletOfEnemy2(int startX, int startY, int bulletDamage, int bulletVelocity, double vx, double vy);

};