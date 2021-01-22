#include "player.h"
#include "graphics.h"
#include "game.h"
using namespace graphics;

Player::Player(const Game& mygame) : GameObject(mygame) {

}

void Player::update() {
	if (getKeyState(SCANCODE_W)&& player1) {
		pos_y -= speed * getDeltaTime() / 10.0f;
	}
	if (getKeyState(SCANCODE_S) && player1) {
		pos_y += speed * getDeltaTime() / 10.0f;
	}
	if (getKeyState(SCANCODE_I) && !player1) {
		pos_y -= speed * getDeltaTime() / 10.0f;
	}
	if (getKeyState(SCANCODE_K) && !player1) {
		pos_y += speed * getDeltaTime() / 10.0f;
	}

	if (pos_y < 50) pos_y = 50;
	if (pos_y > CANVAS_HEIGHT - 50) pos_y = CANVAS_HEIGHT - 50;
}

void Player::draw() {

	Brush br;
	br.outline_opacity = 0.0f;
	setScale(height, height);
	br.fill_opacity = 1.0f;
	br.texture = std::string(ASSET_PATH) + "paddle.png";
	drawRect(pos_x, pos_y, 100, 100, br);


	if (game.getDebugMode()) {
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 0.3f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		Rectangle rect = getCollisionHull2();
		drawRect(rect.cx, rect.cy, rect.size1, rect.size2, br);

	}
}

void Player::init() {

}

Disk Player::getCollisionHull() const {
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 55.0f;
	return disk;
}

Rectangle Player::getCollisionHull2() const {
	Rectangle rect;
	rect.cx = pos_x;
	rect.cy = pos_y;
	rect.size1 = 20.0f;
	rect.size2 = 100.0f;
	return rect;
}


