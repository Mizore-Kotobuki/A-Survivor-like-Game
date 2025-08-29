#include"BulletOfEnemy2.h"
BulletOfEnemy2::BulletOfEnemy2(int startX, int startY, int bulletDamage, int bulletVelocity, double vx, double vy)
    : Bullet(_T("./resource/111.jpg"), startX, startY, bulletDamage, bulletVelocity, vx, vy) {};
