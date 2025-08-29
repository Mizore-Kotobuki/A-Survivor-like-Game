#include"Prop.h"
#include"Player.h"
#include"function.h"
Prop::Prop(int a) { type = a; }
void Prop::draw() {
	IMAGE img1, img2;
	loadimage(&img1, _T("./resource/prop_health.jpg"), 30, 30);
	loadimage(&img2, _T("./resource/prop_power.jpg"), 30, 30);
	if (visibility == 1) {
		if (type == 1)
			putimage(x - 15, y - 15, &img1);
		if (type == 2)
			putimage(x - 15, y - 15, &img2);
	}
}
void Prop::is_picked_up(Player* player) {
	if (visibility == 1) 
		if (isInBetween(-35, 35, player->getX()+20 - x) && isInBetween(-35, 35, player->getY()+20 - y)) {
			visibility = 0;
			if (type == 1)
				player->attributeBoost(0);
			if (type == 2)
				player->attributeBoost(2);
		}
}
void Prop::setx(int a) { x = a; }
void Prop::sety(int b) { y = b; }
void Prop::setvisibility(int a) { visibility = a; }
bool Prop::getvisibility() { return visibility; }