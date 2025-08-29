//
//
//
//   Created By Lloyd_Hayashi
//
//
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
#include<fstream>

#include"Bullet.h"
#include"Obstacle.h"
#include"Bullet_1.h"
#include"Bullet_2.h"
#include"BulletOfEnemy2.h"
#include"Player.h"
#include"Player_1.h"
#include"Player_2.h"
#include"Enemy.h"
#include"Enemy_1.h"
#include"Enemy_2.h"
#include"Prop.h"

#include"macro.h"
#include"function.h"
#include"const.h"
#include"edge.h"
using namespace std;
vector<Obstacle*> obstacles;
vector<Enemy_1*> _1enemies;
vector<Enemy_2*> _2enemies;
Player* player = nullptr;
Prop health(1);
Prop power(2);
bool save = 0;
int figure_choice = 0;
int total_money = 10000; //金币总量
int get_money = 0;  //新获取的金币
int magnification = 1; //金币获取倍率
int game_initialize = 0; 
//0:未完成初始化   1:完成初始化   2：玩家复活初始化

int health_rank = 1;  //四个全局强化等级
int power_rank = 1;
int money_rank = 1;
int resurrection_rank = 1;

int life_left = 1;  //剩余生命
int game_state = 0;
/*
0:开始界面
1：商店
2:选人物
3:游戏中
4：死亡
5：通关
*/
fstream f;
clock_t lastEnemyGenerationTime_1;
clock_t lastEnemyGenerationTime_2;
int main()
{
    initgraph(_GRAPH_WIDTH_, _GRAPH_HEIGHT_);

    IMAGE start, title, startbutton, phealth, plevel, pexp, timeLeft, pass,fail,shop_interface,shop,money_title,back;
    loadimage(&start, _T("./resource/Background.jpg"));
    loadimage(&title, _T("./resource/title.jpg"));
    loadimage(&startbutton, _T("./resource/StartButton.jpg"));
    loadimage(&phealth, _T("./resource/health.jpg"));
    loadimage(&plevel, _T("./resource/level.jpg"));
    loadimage(&pexp, _T("./resource/exp.jpg"));
    loadimage(&timeLeft, _T("./resource/timeLeft.jpg"));
    loadimage(&pass, _T("./resource/pass.jpg"));
    loadimage(&fail, _T("./resource/fail.jpg"));
    loadimage(&shop_interface, _T("./resource/shop_interface.jpg"),_GRAPH_WIDTH_,_GRAPH_HEIGHT_);
    loadimage(&shop, _T("./resource/shop.jpg"));
    loadimage(&back, _T("./resource/back.jpg"));
    loadimage(&money_title, _T("./resource/money_title.jpg"),170,55);
    IMAGE choice, c1, c2;
    loadimage(&choice, _T("./resource/choice.jpg"));
    loadimage(&c1, _T("./resource/c1.jpg"));
    loadimage(&c2, _T("./resource/c2.jpg"));

    IMAGE background;
    loadimage(&background, _T("./resource/Background_.jpg"));
    while (1) {
        //cout << game_state;
        if (game_state == 0) {
            BeginBatchDraw();
            cleardevice();
            putimage(0, 0, &start);
            putimage(330, 160, &title);
            putimage(450, 360, &startbutton);
            putimage(400, 500, &shop);
            if (MouseHit())
            {
                MOUSEMSG msg = GetMouseMsg();
                int x = msg.x;
                int y = msg.y;
                if (msg.uMsg == WM_LBUTTONDOWN && isInBetween(450, 690, x) && isInBetween(360, 440, y))
                  game_state = 2;
                if (msg.uMsg == WM_LBUTTONDOWN && isInBetween(400, 735, x) && isInBetween(500, 615, y))
                    game_state = 1;
               //     cout << x << " " << y << endl;
            }
            EndBatchDraw();
            if (GetAsyncKeyState(13)&&save==1)
                game_state = 3;
        }
        if (game_state == 1) { //商店
            BeginBatchDraw();
            cleardevice();
            wchar_t money[10] = {};
            _itow_s(total_money, money, 10);
            putimage(100, 30, &shop_interface);
            putimage(400, 50, &shop);
            putimage(800, 75, &money_title);
            settextstyle(40, 0, _T("ALGERIAN"));
            outtextxy(980, 80, money);
            int health_cost = health_rank * 300;
            int power_cost = power_rank * 300;
            int money_cost = money_rank * 1000;
            int resurrection_cost =( resurrection_rank + 1) * 1000;
            int costs[4] = { health_cost,power_cost,money_cost,resurrection_cost };
            wchar_t health_cost_T[10] = {};
            wchar_t power_cost_T[10] = {};
            wchar_t money_cost_T[10] = {};
            wchar_t resurrection_cost_T[10] = {};
            wchar_t health_rank_T[10] = {};
            wchar_t power_rank_T[10] = {};
            wchar_t money_rank_T[10] = {};
            wchar_t resurrection_rank_T[10] = {};
            _itow_s(health_cost,health_cost_T , 10);
            _itow_s(power_cost, power_cost_T, 10);
            _itow_s(money_cost,money_cost_T, 10);
            _itow_s(resurrection_cost, resurrection_cost_T, 10);
            _itow_s(health_rank, health_rank_T, 10);
            _itow_s(power_rank, power_rank_T, 10);
            _itow_s(money_rank, money_rank_T, 10);
            _itow_s(resurrection_rank, resurrection_rank_T, 10);
            wchar_t* costs_T[4] = {health_cost_T,power_cost_T,money_cost_T,resurrection_cost_T};
            wchar_t* ranks_T[4] = { health_rank_T,power_rank_T,money_rank_T,resurrection_rank_T };
            int* ranks[4] = { &health_rank,&power_rank,&money_rank,&resurrection_rank };
            int locationy_rank = 215;
            for (int i = 0; i < 4; i++) {//输出等级
                outtextxy(880, locationy_rank, ranks_T[i]);
                locationy_rank += 125;
            }
            int locationy_cost = 263;
            for (int i = 0; i < 4; i++) {  //输出花费
                if (*ranks[i] == 4) {
                    outtextxy(860, locationy_cost, _T("已满级"));
                }
                else {
                    setbkmode(TRANSPARENT);
                    outtextxy(860, locationy_cost, _T("$"));
                    outtextxy(885, locationy_cost, costs_T[i]);
                }
                locationy_cost += 125;
            }
            if (MouseHit())
            {
                MOUSEMSG msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN) {
                    int x = msg.x;
                    int y = msg.y;
                    int location_mouse_up = 212;
                    int location_mouse_down = 298;
                    if (isInBetween(115, 335, x) && isInBetween(45, 130, y))
                        game_state = 0;

                    for (int i = 0; i < 4; i++) {
                        if (isInBetween(150, 660, x) && isInBetween(location_mouse_up, location_mouse_down, y)) 
                            if (*ranks[i] < 4 && total_money >= costs[i]) {
                                *ranks[i] += 1;
                                total_money -= costs[i];
                            }
                        location_mouse_down += 125;
                        location_mouse_up += 125;
                    }
                }
                
            }
            EndBatchDraw();
        }
        if (game_state == 2) {
            game_initialize = 0;
            BeginBatchDraw();
            cleardevice();
            putimage(0, 0, &start);
            putimage(310, 120, &choice);
            putimage(380, 360, &c1);
            putimage(610, 360, &c2);
            if (MouseHit())
            {
                MOUSEMSG msg = GetMouseMsg();
                int x = msg.x;
                int y = msg.y;
                if (msg.uMsg == WM_LBUTTONDOWN)
                {
                    if (x >= 380 && x <= 530 && y >= 360 && y <= 440) {
                        figure_choice = 1;
                        game_state = 3;
                    }
                    else if (x >= 610 && x <= 760 && y >= 360 && y <= 440) {
                        figure_choice = 2;
                        game_state = 3;
                    }
                }
            }
            EndBatchDraw();
        }
        if (game_state == 4) {
            BeginBatchDraw();
            cleardevice();
            putimage(100, 100, &fail);
            wchar_t money[5]{};
            _itow_s(get_money, money, 10);
            settextstyle(50, 0, _T("ALGERIAN"));
            outtextxy(730, 320, money);
            EndBatchDraw();
            if (MouseHit())
            {
                MOUSEMSG msg = GetMouseMsg();
                int x = msg.x;
                int y = msg.y;
                if (msg.uMsg == WM_LBUTTONDOWN&& x >= 380 && x <= 690 && y >= 395 && y <= 500)
                   game_state = 0;
            }
        }
        if (game_state == 5) {
            BeginBatchDraw();
            cleardevice();
            putimage(100, 100, &pass); 
            wchar_t money[5]{};
            _itow_s(get_money, money, 10);
            settextstyle(50, 0, _T("ALGERIAN"));
            outtextxy(730, 300, money);
            EndBatchDraw();
            if (MouseHit())
            {
                MOUSEMSG msg = GetMouseMsg();
                int x = msg.x;
                int y = msg.y;

                if (msg.uMsg == WM_LBUTTONDOWN)
                    if (x >= 385 && x <= 700 && y >= 400 && y <= 503)
                        game_state = 0;
            }
        }
        if (game_state == 3) {
            srand(clock());
            static int gametime;
            if (game_initialize == 0) {
                obstacles.clear();
                _1enemies.clear();
                _2enemies.clear();
                delete player;
                get_money = 0;
                for (int i = 0; i < _NUM_OF_OBSTALCES_; i++)
                {
                    Obstacle* obsc = new Obstacle(obstacles);
                }
                switch (figure_choice)
                {
                case 1:
                    player = new Player_1(health_rank,power_rank);
                    break;

                case 2:
                    player = new Player_2(health_rank,power_rank);
                    break;
                }
                life_left = resurrection_rank;
                lastEnemyGenerationTime_1 = 0;
                lastEnemyGenerationTime_2 = 0;
                gametime = clock();
                game_initialize = 1;
            }
            if (game_initialize == 2) {
                delete player;
                switch (figure_choice)
                {
                case 1:
                    player = new Player_1(health_rank, power_rank);
                    break;

                case 2:
                    player = new Player_2(health_rank, power_rank);
                    break;
                }
                game_initialize = 1;
            }
            if(game_initialize==1) {
                BeginBatchDraw();
                cleardevice();
                int initialLevel = player->getLevel();
            //    cout << "a";
                // the movement of the player
                if (timer(0, 100)) {
                    get_money++;
                    if (GetAsyncKeyState(65)) {
                        player->move(-1, 0, obstacles);
                    }
                    if (GetAsyncKeyState(68)) {
                        player->move(1, 0, obstacles);
                    }
                    if (GetAsyncKeyState(83)) {
                        player->move(0, 1, obstacles);
                    }
                    if (GetAsyncKeyState(87)) {
                        player->move(0, -1, obstacles);
                    }
                }
          //      cout << "b";

                // generation of the enemies
                clock_t currentTime = clock()-gametime;

                int countdown = currentTime / 1000;

                double timeDifference_1 = (double)(currentTime - lastEnemyGenerationTime_1) / CLOCKS_PER_SEC * 1000;
                double timeDifference_2 = (double)(currentTime - lastEnemyGenerationTime_2) / CLOCKS_PER_SEC * 1000;

          //      cout << "c";
                if (timeDifference_1 >= _ENEMY_1_GENERATION_INTERVAL_)
                {
                    Enemy_1* newEnemy = new Enemy_1(_1enemies);
                    _1enemies.push_back(newEnemy);

                    lastEnemyGenerationTime_1 = currentTime;
                }

                for (auto it = _1enemies.begin(); it != _1enemies.end(); ++it)
                {
                    (*it)->load();
                    if ((*it)->isDead())
                    {
                        if ((*it)->vovan()) {
                            int chosen_number = rand() % 21;    //从0-20间随机抽一个数
                            cout << chosen_number;
                            if (chosen_number < 4 && health.getvisibility() == 0) {      //抽中生命道具
                                health.setvisibility(1);
                                health.setx((*it)->getX() + 20); //道具出现在敌人被消灭位置
                                health.sety((*it)->getY() + 20);
                            }
                            if (chosen_number > 17 && power.getvisibility() == 0) {      //抽中生命道具
                                power.setvisibility(1);
                                power.setx((*it)->getX() + 20); //道具出现在敌人被消灭位置
                                power.sety((*it)->getY() + 20);
                            }
                        }
                        (*it)->changort();
                        (*it)->iye(_NICHT_ESIST_ENCIA_);
                    }
                    else // follow the player
                    {
                        double x1 = (*it)->getX() + (*it)->getWidth() / 2;
                        double y1 = (*it)->getY() + (*it)->getHeight() / 2;
                        double x2 = player->getX() + (*it)->getWidth() / 2;
                        double y2 = player->getY() + (*it)->getHeight() / 2;

                        double dx = x2 - x1;
                        double dy = y2 - y1;

                        double distance = pow(dx, 2) + pow(dy, 2);
                        if (abs(dx) >= ((*it)->getWidth() + player->getWidth()) / 2
                            || abs(dy) >= ((*it)->getHeight() + player->getHeight()) / 2)
                        {
                            double sx = dx / sqrt(distance);
                            double sy = dy / sqrt(distance);

                            (*it)->move(sx, sy, obstacles);
                        }
                        else (*it)->Attack(*player);
                    }
                }


                if (timeDifference_2 >= _ENEMY_2_GENERATION_INTERVAL_)
                {
                    Enemy_2* newEnemy = new Enemy_2(_2enemies);
                    _2enemies.push_back(newEnemy);

                    lastEnemyGenerationTime_2 = currentTime;
                }
          //      cout << "d";
                for (auto it = _2enemies.begin(); it != _2enemies.end(); ++it)
                {
                    if ((*it)->isDead())
                    {
                        if ((*it)->Enemy::vovan()) {
                            int chosen_number = rand() % 21;    //从0-20间随机抽一个数
                            if (chosen_number < 4 && health.getvisibility() == 0) {      //抽中生命道具
                                health.setvisibility(1);
                                health.setx((*it)->Enemy::getX()+20); //道具出现在敌人被消灭位置
                                health.sety((*it)->Enemy::getY() + 20);
                            }
                            if (chosen_number > 17 && power.getvisibility() == 0) {      //抽中生命道具
                                power.setvisibility(1);
                                power.setx((*it)->Enemy::getX() + 20); //道具出现在敌人被消灭位置
                                power.sety((*it)->Enemy::getY() + 20);
                            }
                        }
                        (*it)->Enemy::changort();
                        (*it)->Enemy::iye(_NICHT_ESIST_ENCIA_);
                    }
                    else // move in a randomly appointed direction
                    {
                        (*it)->move(obstacles);

                        double currentX = (*it)->Enemy::getX();
                        double currentY = (*it)->Enemy::getY();
                        int current_position = -1;

                        // if touch the margin, change a direction
                        if (currentX <= 0)
                        {
                            current_position = LEFT_EDGE;
                        }
                        else if (currentX >= -60 + _GRAPH_WIDTH_ - (*it)->getWidth())
                        {
                            current_position = RIGHT_EDGE;
                        }
                        else if (currentY <= 60)
                        {
                            current_position = TOP_EDGE;
                        }
                        else if (currentY >= _GRAPH_HEIGHT_ - (*it)->getHeight())
                        {
                            current_position = BOTTOM_EDGE;
                        }

                        random_device rd;
                        mt19937 gen(rd());
                        uniform_real_distribution<double> dis(-1.0, 1.0);
                        double tmpVx = 0;
                        double tmpVy = 0;
                        switch (current_position)
                        {
                        case LEFT_EDGE:
                            tmpVy = dis(gen);
                            tmpVx = sqrt(1 - pow(tmpVy, 2));
                            (*it)->resetVelocity(tmpVx, tmpVy);
                            break;

                        case RIGHT_EDGE:
                            tmpVy = dis(gen);
                            tmpVx = -sqrt(1 - pow(tmpVy, 2));
                            (*it)->resetVelocity(tmpVx, tmpVy);
                            break;

                        case TOP_EDGE:
                            tmpVx = dis(gen);
                            tmpVy = sqrt(1 - pow(tmpVx, 2));
                            (*it)->resetVelocity(tmpVx, tmpVy);
                            break;

                        case BOTTOM_EDGE:
                            tmpVx = dis(gen);
                            tmpVy = -sqrt(1 - pow(tmpVx, 2));
                            (*it)->resetVelocity(tmpVx, tmpVy);
                            break;

                        default:
                            break;

                        }
                    }
                }
          //      cout << "e";
                // renew the graph
                putimage(0, 60, &background);
                putimage(10, 10, &phealth);
                putimage(520, 10, &plevel);
                putimage(650, 10, &pexp);
                putimage(980, 10, &timeLeft);
                health.draw();
                power.draw();
                health.is_picked_up(player);
                power.is_picked_up(player);
                int min = (90 - countdown) / 60;
                int sec1 = ((90 - countdown) % 60) / 10;
                int sec2 = (90 - countdown) % 10;

                settextstyle(30, 0, _T("ALGERIAN"));
                wstring lmin = to_wstring(min), lsec1 = to_wstring(sec1), lsec2 = to_wstring(sec2);
                const wchar_t* lminStr = lmin.c_str(), * lsec1Str = lsec1.c_str(), * lsec2Str = lsec2.c_str();

                outtextxy(985, 30, lminStr);
                outtextxy(1005, 30, L':');
                outtextxy(1015, 30, lsec1Str);
                outtextxy(1035, 30, lsec2Str);


                for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
                {
                    (*it)->draw();
                }
          //      cout << "f";
                player->draw();
                player->update(obstacles, _1enemies, _2enemies);
                player->drawBullets();
          //      cout << "g";
                for (auto it = _1enemies.begin(); it != _1enemies.end(); ++it)
                {
                    (*it)->draw();
                }

                for (auto it = _2enemies.begin(); it != _2enemies.end(); ++it)
                {
                    (*it)->Enemy::draw();
                    (*it)->update(*player, obstacles);
                    (*it)->updateBombs(*player, obstacles);
                    (*it)->drawBombs();
                }

           //     cout << "h";

                if (!min && !sec1 && !sec2)
                {
                    game_state = 5;
                    total_money += get_money*money_rank;
                    game_initialize = 0;
                }
          //      cout << "i";
                if (player->isDead())
                {
                    if (life_left == 1) {
                        game_state = 4;
                        total_money += get_money * money_rank;
                        game_initialize = 0;
                    }
                    else {
                        life_left -= 1;
                        game_initialize = 2;
                    }
                }
          //      cout << "j";
                if (initialLevel != player->getLevel())
                {
                    while (true)
                    {
                        IMAGE* up[4] = { nullptr };

                        up[0] = new IMAGE;
                        loadimage(up[0], _T("./resource/up11.jpg"));
                        up[1] = new IMAGE;
                        loadimage(up[1], _T("./resource/up12.jpg"));
                        up[2] = new IMAGE;
                        loadimage(up[2], _T("./resource/up21.jpg"));
                        up[3] = new IMAGE;
                        loadimage(up[3], _T("./resource/up22.jpg"));

                        random_device rd;
                        mt19937 gen1(rd()), gen2(rd());
                        uniform_int_distribution<int> dis(0, 1);


                        int up1 = dis(gen1), up2 = dis(gen2);
                        int record[3] = { 0 };
                        int startY = 240, k = 0;


                        for (int i = 0; i < 4; i++)
                        {
                            cout << i;
                            if (i != 2 * up1 + up2)
                            {
                                putimage(480, startY, up[i]);
                                record[k++] = i;
                                startY += 100;
                            }
                        }
                        FlushBatchDraw();
                        while (true)
                        {
                            if (MouseHit())
                            {
                                MOUSEMSG msg = GetMouseMsg();
                                int x = msg.x;
                                int y = msg.y;

                                if (msg.uMsg == WM_LBUTTONDOWN)
                                {
                                    if (isInBetween(480, 650, x) && isInBetween(240, 280, y))
                                    {
                                        player->attributeBoost(record[0]);
                                        cleardevice();
                                        break;
                                    }
                                    if (isInBetween(480, 650, x) && isInBetween(340, 380, y))
                                    {
                                        player->attributeBoost(record[1]);
                                        cleardevice();
                                        break;
                                    }
                                    if (isInBetween(480, 650, x) && isInBetween(440, 480, y))
                                    {
                                        player->attributeBoost(record[2]);
                                        cleardevice();
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
              //  cout << "k";
                EndBatchDraw();
                if (GetAsyncKeyState(27)) {
                    game_state = 0;
                    save = 1;
                }
                Sleep(20);
            }
        }
    }
    return 0;

}