#include"Enemy.h"
#include"macro.h"
#include"const.h"
#include"Player.h"
Enemy::Enemy()
{
    width = objectWidth;
    height = objectHeight;
};

void Enemy::draw()
{
    if (vovan())
    {
        putimage((int)x, (int)y, &enemy);
    }
}

int Enemy::getWidth() const
{
    return width;
}

int Enemy::getHeight() const
{
    return height;
}

double Enemy::getX() const
{
    return x;
}

double Enemy::getY() const
{
    return y;
}

void Enemy::changort() { attack = _NICHT_ESIST_ENCIA_; }

void Enemy::iye(int esistencia) { sushchest = esistencia; }

int Enemy::vovan() { return sushchest; }

void Enemy::beAttacked(int bulletDamage, Player& p)
{
    bool flag = (health > 0);
    health -= bulletDamage;
    if (flag && isDead()) p.getExp(exp);
}

bool Enemy::isDead()
{
    return health <= 0;
}