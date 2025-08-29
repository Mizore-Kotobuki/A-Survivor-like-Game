#include"Enemy_1.h"
#include"const.h"
#include"macro.h"
#include"edge.h"
#include"Obstacle.h"
#include"Player.h"
Enemy_1::Enemy_1(vector<Enemy_1*>& _1enemies)
{

    loadimage(&enemy, _T("./resource/1.jpg"));
    health = enemy1Health;
    attack = enemy1Attack;
    sushchest = !_NICHT_ESIST_ENCIA_;
    velocity = enemy1Velocity;
    exp = 10;

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
        x = leftEdge;
        y = dis2(gen) * _GRID_LENGTH_;
        break;

    case RIGHT_EDGE:
        x = rightEdge;
        y = dis2(gen) * _GRID_LENGTH_;
        break;

    case TOP_EDGE:
        x = dis3(gen) * _GRID_LENGTH_;
        y = topEdge;
        break;

    case BOTTOM_EDGE:
        x = dis3(gen) * _GRID_LENGTH_;
        y = bottomEdge;
        break;

    default:
        break;

    }

    _1enemies.push_back(this);

}


void Enemy_1::move(double dx, double dy,vector<Obstacle*>& obstacles)
{
    double targetX = x + dx * velocity;
    double targetY = y + dy * velocity;

    // the region occupied by the player
    double enemyLeft = targetX;
    double enemyRight = targetX + enemy.getwidth();
    double enemyTop = targetY;
    double enemyBottom = targetY + enemy.getheight();

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

    if (collided && obstacleToAvoid != nullptr)
    {
        // Adjust the enemy's direction based on the collide position
        switch (collidePos)
        {
        case LEFT_EDGE:
        case RIGHT_EDGE:
            dx = 0;
            dy = dy / abs(dy);
            break;

        case TOP_EDGE:
        case BOTTOM_EDGE:
            dy = 0;
            dx = dx / abs(dx);
            break;

        default:
            break;

        }
    }

    x += dx * velocity;
    y += dy * velocity;

}

void Enemy_1::Attack(Player& p)
{
    p.beAttacked(enemy1Attack);
    loadimage(&enemy, _T("./resource/enemy_attacking.jpg"));
}
void Enemy_1::load() {
    loadimage(&enemy, _T("./resource/1.jpg"));
}