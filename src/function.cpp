#include"function.h"
#include"macro.h"
#include<time.h>
bool isInBetween(int p, int q, double x)
{
    if (p < x && x < q) return true;

    return false;
}

bool isMouseInsideButton(int mouseX, int mouseY, int buttonX, int buttonY, int buttonWidth, int buttonHeight)
{
    return (mouseX >= buttonX && mouseX <= buttonX + buttonWidth && mouseY >= buttonY &&
        mouseY <= buttonY + buttonHeight);
}

bool isInsideGraph(double left, double right, double top, double bottom)
{
    if (left < 0 || right > _GRAPH_WIDTH_ - 60 || top < 60 || bottom > _GRAPH_HEIGHT_) return false;

    return true;
}
bool timer(int id, int duration) {
    static int timer[20];
    if (clock() - timer[id] > duration) {
        timer[id] = clock();     
        return 1;
    }
    return 0;
}
