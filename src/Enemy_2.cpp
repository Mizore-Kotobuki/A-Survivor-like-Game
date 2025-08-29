#include"Enemy_2.h"
#include"edge.h"
#include"function.h"
#include"const.h"
#include"macro.h"
#include"Player.h"
#include"Obstacle.h"
using namespace std;
Enemy_2::Enemy_2(vector<Enemy_2*>& _2enemies)
{

    loadimage(&enemy, _T("./resource/11.jpg"));
    health = enemy2Health;
    attack = enemy2Attack;
    Enemy::sushchest = !_NICHT_ESIST_ENCIA_;
    Enemy::velocity = enemy2Velocity;
    exp = 25;

    int leftEdge = 0;
    int rightEdge = -60 + _GRAPH_WIDTH_ - getWidth();
    int topEdge = 60;
    int bottomEdge = _GRAPH_HEIGHT_ - getHeight();


    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dis1(0, 3);
    uniform_int_distribution<int> dis2(1, 10);
    uniform_int_distribution<int> dis3(0, 17);


    switch (dis1(gen))
    {
    case LEFT_EDGE:
        pos = LEFT_EDGE;
        Enemy::x = leftEdge;
        Enemy::y = dis2(gen) * _GRID_LENGTH_;
        break;

    case RIGHT_EDGE:
        pos = RIGHT_EDGE;
        Enemy::x = rightEdge;
        Enemy::y = dis2(gen) * _GRID_LENGTH_;
        break;

    case TOP_EDGE:
        pos = TOP_EDGE;
        Enemy::x = dis3(gen) * _GRID_LENGTH_;
        Enemy::y = topEdge;
        break;

    case BOTTOM_EDGE:
        pos = BOTTOM_EDGE;
        Enemy::x = dis3(gen) * _GRID_LENGTH_;
        Enemy::y = bottomEdge;
        break;

    default:
        break;

    }

    uniform_real_distribution<double> dis4(-1.0, 1.0);

    switch (pos)
    {
    case LEFT_EDGE:
        vy = dis4(gen);
        vx = sqrt(1 - pow(vy, 2));
        break;

    case RIGHT_EDGE:
        vy = dis4(gen);
        vx = -sqrt(1 - pow(vy, 2));
        break;

    case TOP_EDGE:
        vx = dis4(gen);
        vy = sqrt(1 - pow(vy, 2));
        break;

    case BOTTOM_EDGE:
        vx = dis4(gen);
        vy = -sqrt(1 - pow(vy, 2));
        break;

    default:
        break;

    }

    _2enemies.push_back(this);

}


void Enemy_2::move(vector<Obstacle*>& obstacles)
{
    double targetX = Enemy::x + vx * Enemy::velocity;
    double targetY = Enemy::y + vy * Enemy::velocity;

    // the region occupied by the player
    double enemyLeft = targetX;
    double enemyRight = targetX + getWidth();
    double enemyTop = targetY;
    double enemyBottom = targetY + getHeight();

    // check whether collide with the obstacle
    bool collided = false;
    int collidePos = -1;
    Obstacle* obstacleToAvoid = nullptr;
    for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
    {
        Obstacle* obstacle = *it;
        int obstacleLeft = obstacle->getLx();
        int obstacleRight = obstacle->getRx();
        int obstacleTop = obstacle->getUy();
        int obstacleBottom = obstacle->getLy();

        if (enemyLeft < obstacleRight && enemyRight > obstacleLeft &&
            enemyTop < obstacleBottom && enemyBottom > obstacleTop)
        {
            collided = true;

            // Determine the collide position
            double overlapLeft = obstacleRight - enemyLeft;
            double overlapRight = enemyRight - obstacleLeft;
            double overlapTop = obstacleBottom - enemyTop;
            double overlapBottom = enemyBottom - obstacleTop;

            if (overlapLeft < getWidth() && overlapLeft <= overlapRight &&
                overlapLeft <= overlapTop && overlapLeft <= overlapBottom)
            {
                collidePos = RIGHT_EDGE;
            }
            else if (overlapRight < getWidth() && overlapRight <= overlapLeft &&
                overlapRight <= overlapTop && overlapRight <= overlapBottom)
            {
                collidePos = LEFT_EDGE;
            }
            else if (overlapTop < getHeight() && overlapTop <= overlapLeft &&
                overlapTop <= overlapRight && overlapTop <= overlapBottom)
            {
                collidePos = BOTTOM_EDGE;
            }
            else if (overlapBottom < getHeight() && overlapBottom <= overlapLeft &&
                overlapBottom <= overlapRight && overlapBottom <= overlapTop)
            {
                collidePos = TOP_EDGE;
            }

            obstacleToAvoid = obstacle;
            break;

        }
    }

    if (collidePos == -1 && isInsideGraph(enemyLeft, enemyRight, enemyTop, enemyBottom))
    {
        Enemy::x = targetX;
        Enemy::y = targetY;
        return;
    }

    if (collidePos != -1 && obstacleToAvoid)
    {
        // choose the route to follow the player
        switch (collidePos)
        {
        case LEFT_EDGE:
        case RIGHT_EDGE:
            resetVelocity(-vx, vy);
            break;

        case TOP_EDGE:
        case BOTTOM_EDGE:
            resetVelocity(vx, -vy);
            break;

        default:
            break;

        }

    }

    Enemy::x += vx * Enemy::velocity;
    Enemy::y += vy * Enemy::velocity;

}

void Enemy_2::resetVelocity(double newVx, double newVy)
{
    vx = newVx;
    vy = newVy;
}

void Enemy_2::update(Player& p, vector<Obstacle*>& obstacles)
{

    DWORD currentTime = GetTickCount();
    if (currentTime - lastAttackTime >= _BOMB_RELEASE_INTERVAL_)
    {
        if ((vx || vy) && Enemy::vovan()) Attack(p);

        lastAttackTime = currentTime;
    }

    updateBombs(p,obstacles);

}

void Enemy_2::Attack(Player& p)
{
    int startX = Enemy::x - 5 + getWidth() / 2;
    int startY = Enemy::y - 5 + getHeight() / 2;
    int Vb = 2 * Enemy::velocity;
    int enemy2BombDirection = 12;

    double direction[12][2] =
    {
        { 1.000, 0.000},{ 0.866, 0.500},{ 0.500, 0.866},
        { 0.000, 1.000},{-0.500, 0.866},{-0.866, 0.500},
        {-1.000, 0.000},{-0.866,-0.500},{-0.500,-0.866},
        { 0.000,-1.000},{ 0.500,-0.866},{ 0.866,-0.500}
    };

    for (int i = 0; i < enemy2BombDirection; i++)
    {
        BulletOfEnemy2* bomb = new BulletOfEnemy2(startX, startY, attack, Vb, direction[i][0], direction[i][1]);
        bombs.push_back(bomb);
    }

}


bool Enemy_2::hitPlayer(BulletOfEnemy2* b, Player& p)
{
    double xp = p.getX();
    double yp = p.getY();
    int pWidth = p.getWidth();
    int pHeight = p.getHeight();

    if (b->getX() + 10 >= xp && b->getX() <= xp + pWidth &&
        b->getY() + 10 >= yp && b->getY() <= yp + pHeight)
    {
        p.beAttacked(attack);
        return true;
    }

    return false;
}


void Enemy_2::updateBombs(Player& p,vector<Obstacle*>& obstacles)
{
    for (auto it = bombs.begin(); it != bombs.end(); ++it)
    {
        BulletOfEnemy2* bomb = *it;

        if (bomb->move(obstacles))
        {
            bool bombHit = false;

            if (hitPlayer(bomb, p))
            {
                bomb->iye(_NICHT_ESIST_ENCIA_);
                bomb->changort();
                bombHit = true;
                break;
            }
        }
        else bomb->iye(_NICHT_ESIST_ENCIA_);
    }
}


void Enemy_2::drawBombs()
{
    for (auto bomb : bombs)
    {
        if (bomb->vovan()) bomb->draw();
    }
}