#pragma once
#include <iostream>
#include <graphics.h>
#include <easyx.h>
#include <conio.h>
#include <tchar.h>
#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <thread>
#include <random>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>

#include"Player.h"
#include"Bullet_2.h"
class Player_2 :
    public Player, Bullet_2
{
    vector<Bullet_2*> bullets;

public:
    Player_2(int health_rank, int power_rank);
    void shootBullet() override;
    void updateBullets(vector<Obstacle*>& obstacles, vector<Enemy_1*>& _1enemies, vector<Enemy_2*>& _2enemies);
    void drawBullets() override;
    void attributeBoost(int choice) override;

};