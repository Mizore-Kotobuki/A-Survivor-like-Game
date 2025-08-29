#pragma once
#include"Player.h"
#include"Bullet_1.h"
using namespace std;
class Player_1 :
    public Player, Bullet_1
{
    vector<Bullet_1*> bullets;

public:
    Player_1(int health_rank,int power_rank);
    void shootBullet() override;
    void updateBullets(vector<Obstacle*>& obstacles, vector<Enemy_1*>& _1enemies, vector<Enemy_2*>& _2enemies) ;
    void drawBullets() override;
    void attributeBoost(int choice) override;

};