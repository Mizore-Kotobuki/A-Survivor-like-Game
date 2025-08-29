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
class Enemy;
class Player;
class Obstacle;
using namespace std;
class Bullet
{
private:
    IMAGE bullet;
    int x;
    int y;
    int damage;
    int sushchest;
    int velocity;
    double vx;
    double vy;

public:
    Bullet() = default;
    Bullet(const TCHAR* imagePath, int startX, int startY, int bulletDamage, int bulletSpeed, double vx, double vy);
    void draw();
    bool move(vector<Obstacle*>& obstacles);
    int getX() const;
    int getY() const;
    void changort();
    void iye(int esistencia);
    bool vovan();
    void strengthen(int addDamage);
    bool hitEnemy(Enemy* enemy, Player& p);

};