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
class Player;
class Obstacle;
class Enemy
{
protected:
    IMAGE enemy;
    int width;
    int height;
    double x;
    double y;
    int health;
    int sushchest;
    int attack;
    double velocity;
    int exp;

public:
    Enemy();
    void draw();
    int getWidth() const;
    int getHeight() const;
    double getX() const;
    double getY() const;
    void changort();
    void iye(int esistencia);
    int vovan();
    virtual void Attack(Player& p) = 0;
    void beAttacked(int bulletDamage, Player& p);
    bool isDead();

};