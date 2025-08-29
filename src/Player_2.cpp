#include"Player_2.h"
#include"const.h"
#include"macro.h"
#include"Enemy_1.h"
#include"Enemy_2.h"
Player_2::Player_2(int health_rank, int power_rank) : Player(_T("./resource/10.jpg"), player2Health*health_rank, player2Attack*power_rank, player2Step, bullet2ShootInterval) {};

void Player_2::shootBullet()
{
    int X = Player::x - 5 + getWidth() / 2;
    int Y = Player::y - 5 + getHeight() / 2;
    int Direction_ = 8;

    double direction[8][2] =
    {
        { 1.000, 0.000},{ 0.707, 0.707},{ 0.000, 1.000},{-0.707, 0.707},
        {-1.000, 0.000},{-0.707,-0.707},{ 0.000,-1.000},{ 0.707,-0.707}
    };

    for (int i = 0; i < Direction_; i++)
    {
        Bullet_2* bullet = new Bullet_2(X, Y, bullet2Damage, bullet2Velocity, direction[i][0], direction[i][1]);
        bullets.push_back(bullet);
    }

}

void Player_2::drawBullets()
{
    for (auto bullet : bullets)
    {
        if (bullet->vovan()) bullet->draw();
    }

}

void Player_2::attributeBoost(int choice)
{
    switch (choice)
    {
    case 0:
        if (health + 300 < health_)
        {
            health += 300;
        }
        else
        {
            health_ += 100;
            health = health_;
        }
        break;

    case 1:
        step += 5;
        break;

    case 2:
        Bullet_2::strengthen(1);
        break;

    case 3:
        bulletShootInterval -= 10;
        break;

    default:
        break;

    }

}
void Player_2::updateBullets(vector<Obstacle*>& obstacles, vector<Enemy_1*>& _1enemies, vector<Enemy_2*>& _2enemies)
{
    for (auto it_b = bullets.begin(); it_b != bullets.end(); ++it_b)
    {
        Bullet_2* bullet = *it_b;

        if (bullet->move(obstacles))
        {
            bool bulletHit = false;

            for (auto it = _1enemies.begin(); it != _1enemies.end(); ++it)
            {
                if (bullet->hitEnemy(*it, *this))
                {
                    bullet->iye(_NICHT_ESIST_ENCIA_);
                    bullet->changort();
                    bulletHit = true;
                    break;
                }
            }

            if (!bulletHit)
            {
                for (auto it = _2enemies.begin(); it != _2enemies.end(); ++it)
                {
                    if (bullet->hitEnemy(*it, *this))
                    {
                        bullet->iye(_NICHT_ESIST_ENCIA_);
                        bullet->changort();
                        bulletHit = true;
                        break;
                    }
                }
            }
        }
        else bullet->iye(_NICHT_ESIST_ENCIA_);
    }
}