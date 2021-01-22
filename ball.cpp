#include "ball.h"
#include "graphics.h"
#include "config.h"
#include <random>
#include "util.h"
#include "game.h"
using namespace graphics;

void Ball::update() {

	if (getDirection() == STOP)
		randomDirection();

	Move();
	rotation += 0.05f * getDeltaTime();
	rotation = fmodf(rotation, 360);

	if (pos_x < -size || pos_x > CANVAS_WIDTH + size) {
		active = false;
	}

	//bottom wall
	if (pos_y >= CANVAS_HEIGHT - 1)
		changeDirection(getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);

	//top wall
	if (pos_y <= 1)
		changeDirection(getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

	if (getGlobalTime() > 60000) {
		setSpeed(0.6f);
	}

}

void Ball::draw() {
	setOrientation(rotation);
	brush.texture = std::string(ASSET_PATH) + "ball3-shadow.png";
	brush.fill_opacity = 0.5f;
	drawRect(pos_x-10, pos_y+30, size, size, brush);
	brush.texture = std::string(ASSET_PATH) + "ball3.png";
	brush.fill_opacity = 1.0f;
	drawRect(pos_x, pos_y, size, size, brush);
	resetPose();

	if (game.getDebugMode()) {
		Brush br;
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.3f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		Disk hull = getCollisionHull();
		drawDisk(hull.cx, hull.cy, hull.radius, br);
	}
}

void Ball::init() {
	speed = 0.4f;
	pos_x = CANVAS_WIDTH / 2;
	pos_y = CANVAS_HEIGHT / 2;
	size = 40.0f;
	originalX = pos_x;
	originalY = pos_y;
	direction = STOP;
	brush.outline_opacity = 0.0f;
}

Ball::Ball(const Game & mygame) : GameObject(mygame) {
	init();
}

Ball::~Ball() {
}

Disk Ball::getCollisionHull() const {
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size * 0.45f;
	return disk;
}

Rectangle Ball::getCollisionHull2() const
{
	return Rectangle();
}

void Ball::Reset()
{
	pos_x = originalX;
	pos_y = originalY;
	direction = STOP;
}

void Ball::changeDirection(cDir d)
{
	direction = d;
}

void Ball::randomDirection()
{
	direction = (cDir)((rand() % 6) + 1);
}

void Ball::Move()
{
	switch (direction)
	{
	case STOP:
		break;
	case LEFT:
		pos_x-= speed * getDeltaTime();
		break;
	case RIGHT:
		pos_x+= speed * getDeltaTime();
		break;
	case UPLEFT:
		pos_x-= speed * getDeltaTime();
		pos_y-= speed * getDeltaTime();
		break;
	case UPRIGHT:
		pos_x+= speed * getDeltaTime();
		pos_y-= speed * getDeltaTime();
		break;
	case DOWNRIGHT:
		pos_x+= speed * getDeltaTime();
		pos_y+= speed * getDeltaTime();
		break;
	case DOWNLEFT:
		pos_x-= speed * getDeltaTime();
		pos_y+= speed * getDeltaTime();
		break;
	default:
		break;
	}
}
