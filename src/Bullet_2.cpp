#include"Bullet_2.h"
Bullet_2::Bullet_2() {}

Bullet_2::Bullet_2(int startX, int startY, int bulletDamage, int bulletVelocity, double vx, double vy)
    : Bullet(_T("./resource/1000.jpg"), startX, startY, bulletDamage, bulletVelocity, vx, vy) {};
