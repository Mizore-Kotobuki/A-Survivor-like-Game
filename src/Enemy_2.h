#pragma once
#include"Enemy.h"
#include"Bullet.h"
#include"BulletOfEnemy2.h"
class Enemy_2 :
    public Enemy, public Bullet
{
private:
    vector<BulletOfEnemy2*> bombs;
    int pos;
    double vx;
    double vy;
    double lastAttackTime;

public:
    Enemy_2(vector<Enemy_2*>& _2enemies);
    void move(vector<Obstacle*>& obstacles);
    void resetVelocity(double newVx, double newVy);
    void update(Player& p, vector<Obstacle*>& obstacles);
    void Attack(Player& p);
    bool hitPlayer(BulletOfEnemy2* b, Player& p);
    void updateBombs(Player& p, vector<Obstacle*>& obstacles);
    void drawBombs();

};