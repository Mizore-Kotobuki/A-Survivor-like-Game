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
using namespace std;
class Obstacle
{
    IMAGE obstacle;
    int lx;
    int rx;
    int uy;
    int ly;

public:
    Obstacle(vector<Obstacle*>& obstacles);
    void draw();
    int getLx() const;
    int getRx() const;
    int getUy() const;
    int getLy() const;
    bool checkNewObstacle(Obstacle& newObstacle, vector<Obstacle*>& obstalces);

};