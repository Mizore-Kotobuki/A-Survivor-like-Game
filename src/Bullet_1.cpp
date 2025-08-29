#include"Bullet_1.h"

Bullet_1::Bullet_1() {}
Bullet_1::Bullet_1(int startX, int startY, int bulletDamage, int bulletVelocity, int vx, int vy)
    : Bullet(_T("./resource/100.jpg"), startX, startY, bulletDamage, bulletVelocity, vx, vy) {};