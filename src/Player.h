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
class Obstacle;
class Enemy_1;
class Enemy_2;
using namespace std;
class Player
{
protected:
    IMAGE player;
    int x;
    int y;
    int vx;
    int vy;
    int lv;
    int exp;
    int lvUpExp;
    int step;
    int width;
    int height;
    int attack;
    int health;
    int health_;
    double lastShootTime;
    int bulletShootInterval;

public:
    Player(const TCHAR* imagePath, int pHealth, int pAttack, int pStep, int pShootInterval);
    virtual ~Player();
    virtual void draw();
    int getWidth() const;
    int getHeight() const;
    int getStep() const;
    void move(int dx, int dy, vector<Obstacle*>& obstacles);
    int getVx() const;
    int getVy() const;
    virtual void shootBullet() = 0;
    virtual void updateBullets(vector<Obstacle*>&, vector<Enemy_1*>&, vector<Enemy_2*>&) = 0;
    virtual void drawBullets() = 0;
    void update(vector<Obstacle*>& obstacles, vector<Enemy_1*>& _1enemies, vector<Enemy_2*>& _2enemies);
    void getExp(int exp_);
    int getX() const;
    int getY() const;
    void beAttacked(int attack);
    bool isDead();
    int getLevel() const;
    virtual void attributeBoost(int choice) = 0;

};