#include"Player.h"
#include"macro.h"
#include"const.h"
#include"Obstacle.h"
#include"function.h"
Player::Player(const TCHAR* imagePath, int pHealth, int pAttack, int pStep, int pShootInterval)
    : health(pHealth), health_(pHealth), attack(pAttack), step(pStep), bulletShootInterval(pShootInterval)
{
    loadimage(&player, imagePath);

    lv = 0;
    exp = 0;
    lvUpExp = 50;

    vx = vy = 0;
    width = objectWidth;
    height = objectHeight;

    lastShootTime = 0;

    x = _GRID_LENGTH_ * _GRID_NUM_IN_WIDTH_ / 2;
    y = _GRID_LENGTH_ * (_GRID_NUM_IN_HEIGHT_ + 1) / 2;

}

Player::~Player() {};

void Player::draw()
{
    putimage(x, y, &player);
}

int Player::getWidth() const
{
    return width;
}

int Player::getHeight() const
{
    return height;
}

int Player::getStep() const
{
    return step;
}

void Player::move(int dx, int dy,vector<Obstacle*>& obstacles)
{
    int targetX = x + dx * step;
    int targetY = y + dy * step;

    // the region occupied by the player
    int playerLeft = targetX;
    int playerRight = targetX + getWidth();
    int playerTop = targetY;
    int playerBottom = targetY + getHeight();


    // check whether collide with the obstacle
    bool collided = false;
    for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
    {
        Obstacle* obstacle = *it;
        int obstacleLeft = obstacle->getLx();
        int obstacleRight = obstacle->getRx();
        int obstacleTop = obstacle->getUy();
        int obstacleBottom = obstacle->getLy();

        if (playerLeft < obstacleRight && playerRight > obstacleLeft &&
            playerTop < obstacleBottom && playerBottom > obstacleTop)
        {
            collided = true;

            // Calculate the overlapping distances
            int overlapX = min(playerRight, obstacleRight) - max(playerLeft, obstacleLeft);
            int overlapY = min(playerBottom, obstacleBottom) - max(playerTop, obstacleTop);

            // Adjust the target position based on the overlapping distances
            if (dx < 0)
            {
                targetX += overlapX;
            }
            else if (dx > 0)
            {
                targetX -= overlapX;
            }

            if (dy < 0)
            {
                targetY += overlapY;
            }
            else if (dy > 0)
            {
                targetY -= overlapY;
            }

            break;
        }

    }

    if (!collided && isInsideGraph(playerLeft, playerRight, playerTop, playerBottom))
    {
        x = targetX;
        y = targetY;

        vx = dx;
        vy = dy;
    }

}


int Player::getVx() const
{
    return vx;
}

int Player::getVy() const
{
    return vy;
}

void Player::update(vector<Obstacle*>& obstacles, vector<Enemy_1*>& _1enemies, vector<Enemy_2*>& _2enemies)
{

    DWORD currentTime = GetTickCount();
    if (currentTime - lastShootTime >= bulletShootInterval)
    {
        if (vx || vy) shootBullet();

        lastShootTime = currentTime;
    }

    updateBullets(obstacles,_1enemies,_2enemies);

}

void Player::getExp(int exp_)
{
    if (lv == 15) return;

    exp += exp_;
    int lv_ = lv;

    if (exp >= lvUpExp)
    {
        lv++;
        exp -= lvUpExp;
        lvUpExp += 50;

        if (lv >= 10) lvUpExp += 50;
    }

}

int Player::getX() const
{
    return x;
}

int Player::getY() const
{
    return y;
}

void Player::beAttacked(int attack)
{
    health -= attack;
}

bool Player::isDead()
{
    settextstyle(40, 0, _T("ALGERIAN"));
    wstring llv = to_wstring(lv);
    const wchar_t* lvStr = llv.c_str();
    outtextxy(600, 10, lvStr);

    setfillcolor(RED);
    bar(100, 15, 100 + health / 10, 45);
    setfillcolor(LIGHTGRAY);
    bar(100 + health / 10, 15, 100 + health_ / 10, 45);
    setfillcolor(YELLOW);
    bar(840, 15, 840 + 100 * exp / lvUpExp, 45);
    setfillcolor(LIGHTGRAY);
    bar(840 + 100 * exp / lvUpExp, 15, 940, 45);

    return health <= 0;
}

int Player::getLevel() const
{
    return lv;
}