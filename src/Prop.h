#pragma once
class Player;
class Prop {
	int type ; //1:ÉúÃü 2£º»ğÁ¦
	bool visibility = 0;
	int x, y;
public:
	Prop(int type);
	void setx(int x);
	void sety(int y);
	void setvisibility(int a);
	bool getvisibility();
	void draw();
	void is_picked_up(Player* player);
};