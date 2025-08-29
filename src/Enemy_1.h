#pragma once
#include"Enemy.h"
#include<chrono>
using namespace std;
class Enemy_1 :
    public Enemy
{
private:
    chrono::steady_clock::time_point lastAttackTime;

public:
    void load();
    Enemy_1(vector<Enemy_1*>& _1enemies);
    void move(double dx, double dy, vector<Obstacle*>& obstacles);
    void Attack(Player& p);

};