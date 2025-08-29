#include"Player_1.h"
#include"const.h"
#include"macro.h"
#include"Enemy_1.h"
#include"Enemy_2.h"
Player_1::Player_1(int health_rank,int power_rank) : Player(_T("./resource/0.jpg"), player1Health*health_rank, player1Attack*power_rank, player1Step, bullet1ShootInterval) {};

void Player_1::shootBullet()
{
    Bullet_1* bullet = new Bullet_1(Player::x - 5 + getWidth() / 2, Player::y - 5 + getHeight() / 2, bullet1Damage,
        bullet1Velocity, getVx(), getVy());

    bullets.push_back(bullet);

}

void Player_1::drawBullets()
{
    for (auto bullet : bullets)
    {
        if (bullet->vovan()) bullet->draw();
    }

}

void Player_1::attributeBoost(int choice)
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
        Bullet_1::strengthen(2);
        break;

    case 3:
        bulletShootInterval -= 20;
        break;

    default:
        break;

    }
}
void Player_1::updateBullets(vector<Obstacle*>& obstacles,vector<Enemy_1*>& _1enemies,vector<Enemy_2*>& _2enemies)
{
    for (auto it_b = bullets.begin(); it_b != bullets.end(); ++it_b)
    {
        Bullet_1* bullet = *it_b;

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
