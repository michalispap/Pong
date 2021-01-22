#pragma once

#include "gameobject.h"
#include "config.h"

class Player : public GameObject , public Collidable {
	float speed = 4.0f;
	float pos_x = CANVAS_WIDTH/2, pos_y = CANVAS_HEIGHT/2;
	float height = 1.0f;
	bool player1 = true;
	int score = 0;
public:
	Player(const class Game & mygame);
	void update() override;
	void draw() override;
	void init() override;
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; } 
	int getScore() { return score; }
	void increaseScore() { score++; }
	Disk getCollisionHull() const override;
	Rectangle getCollisionHull2() const override;
	void setPosX(float x) { pos_x = x; }
	void setPlayer(bool p) { player1 = p; }
};