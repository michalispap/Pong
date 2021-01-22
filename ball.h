#pragma once
#include "gameobject.h"
#include "graphics.h"
#include "player.h"
using namespace graphics;
enum cDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };

class Ball : public GameObject, public Collidable {
	float pos_x, pos_y;
	float originalX, originalY;
	cDir direction;
	float speed;
	float size;
	float rotation;
	Brush brush;
	bool active = true;
public:
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	Ball(const class Game & mygame);
	~Ball();
	Disk getCollisionHull() const override;
	Rectangle getCollisionHull2() const override;
	void Reset();
	void changeDirection(cDir d);
	void randomDirection();
	inline int getX() { return pos_x; }
	inline int getY() { return pos_y; }
	inline void setSpeed(float s) { speed = s; }
	inline cDir getDirection() { return direction; }
	void Move();
};
