#include"Bullet.h"
#include"function.h"
#include"macro.h"
#include"Obstacle.h"
#include"Enemy.h"
Bullet::Bullet(const TCHAR* imagePath, int startX, int startY,
    int bulletDamage, int bulletVelocity, double vx, double vy)

    : x(startX), y(startY), damage(bulletDamage), velocity(bulletVelocity), vx(vx), vy(vy)
{
    loadimage(&bullet, imagePath);
    sushchest = true;
}


void Bullet::draw()
{
    putimage(static_cast<int>(x), static_cast<int>(y), &bullet);
}

bool Bullet::move(vector<Obstacle*>& obstacles)
{
    int targetX = x + vx * (double)velocity;
    int targetY = y + vy * (double)velocity;

    // the region occupied by the bullet
    int bulletLeft = targetX;
    int bulletRight = targetX + bullet.getwidth();
    int bulletTop = targetY;
    int bulletBottom = targetY + bullet.getheight();


    // check whether collide with the obstacle
    for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
    {
        Obstacle* obstacle = *it;
        int obstacleLeft = obstacle->getLx();
        int obstacleRight = obstacle->getRx();
        int obstacleTop = obstacle->getUy();
        int obstacleBottom = obstacle->getLy();

        if (bulletLeft < obstacleRight && bulletRight > obstacleLeft &&
            bulletTop < obstacleBottom && bulletBottom > obstacleTop)
        {
            return false;
        }

    }

    if (!isInsideGraph(bulletLeft, bulletRight, bulletTop, bulletBottom))
    {
        return false;
    }

    x = targetX;
    y = targetY;

    return true;
}


int Bullet::getX() const
{
    return x;
}

int Bullet::getY() const
{
    return y;
}

void Bullet::changort() { damage = _NICHT_ESIST_ENCIA_; }

void Bullet::iye(int esistencia) { sushchest = esistencia; }

bool Bullet::vovan() { return sushchest; }

void Bullet::strengthen(int addDamage)
{
    damage += addDamage;
}

bool Bullet::hitEnemy(Enemy* enemy, Player& p)
{
    double enemyX = enemy->getX();
    double enemyY = enemy->getY();
    int enemyWidth = enemy->getWidth();
    int enemyHeight = enemy->getHeight();

    if (x + bullet.getwidth() >= enemyX && x <= enemyX + enemyWidth &&
        y + bullet.getheight() >= enemyY && y <= enemyY + enemyHeight && enemy->vovan())
    {
        enemy->beAttacked(damage, p);
        return true;
    }

    return false;
}