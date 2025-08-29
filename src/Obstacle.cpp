#include"Obstacle.h"
#include"macro.h"

bool Obstacle::checkNewObstacle(Obstacle& newObstacle, vector<Obstacle*>& obstacles)
{
    const int offsets[8][2] =
    {
        {-1,-1}, {-1, 0}, {-1, 1},
        { 0,-1},          { 0, 1},
        { 1,-1}, { 1, 0}, { 1, 1}
    };

    for (Obstacle* obstacle : obstacles)
    {
        int newLx = newObstacle.getLx();
        int newRx = newObstacle.getRx();
        int newUy = newObstacle.getUy();
        int newLy = newObstacle.getLy();

        int obstacleLx = obstacle->getLx();
        int obstacleRx = obstacle->getRx();
        int obstacleUy = obstacle->getUy();
        int obstacleLy = obstacle->getLy();

        // Check if new obstacle is too close to the existing obstacle
        if (newRx + 1 >= obstacleLx && newLx - 1 <= obstacleRx &&
            newLy + 1 >= obstacleUy && newUy - 1 <= obstacleLy)
        {
            return false;
        }

        // Check if new obstacle is within the 8-cell proximity of the existing obstacle
        for (const auto& offset : offsets)
        {
            int offsetX = offset[0] * _GRID_LENGTH_;
            int offsetY = offset[1] * _GRID_LENGTH_;

            if (newRx + 1 + offsetX >= obstacleLx && newLx - 1 + offsetX <= obstacleRx &&
                newLy + 1 + offsetY >= obstacleUy && newUy - 1 + offsetY <= obstacleLy)
            {
                return false;
            }

        }
    }

    return true;
}


Obstacle::Obstacle(vector<Obstacle*>& obstacles)
{
    loadimage(&obstacle, _T("./resource/101.jpg"));

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distX(2, _GRID_NUM_IN_WIDTH_ - 4);
    uniform_int_distribution<int> distY(3, _GRID_NUM_IN_HEIGHT_ - 2);

    while (true)
    {
        lx = distX(gen) * _GRID_LENGTH_;
        rx = lx + obstacle.getwidth();
        uy = distY(gen) * _GRID_LENGTH_;
        ly = uy + obstacle.getheight();

        // Add obstacle only if it meets the distance criteria
        if (checkNewObstacle(*this, obstacles))
        {
            obstacles.push_back(this);
            break;
        }

    }

}
void Obstacle::draw()
{
    putimage(lx, uy, &obstacle);
}

int Obstacle::getLx() const
{
    return lx;
}

int Obstacle::getRx() const
{
    return rx;
}

int Obstacle::getUy() const
{
    return uy;
}

int Obstacle::getLy() const
{
    return ly;
}