#pragma once

#include "player.h"
#include "ball.h"
#include <time.h>
#include <conio.h>
#include <iostream>

class Game {
	typedef enum {STATUS_START, STATUS_PLAYING, STATUS_FINISH} status_t;
	Player * player = nullptr;
	Player* player2 = nullptr;
	bool player_initialized = false;
	bool debug_mode = false;
	Ball * ball = nullptr;
	void spawnBall();
	void checkBall();
	bool checkCollision();
	status_t status = STATUS_START;
	const int end_score = 10;

	unsigned int window_width = WINDOW_WIDTH,
		         window_height = WINDOW_HEIGHT;

	void updateStartScreen();
	void updateLevelScreen();
	void updateEndScreen();
	void drawStartScreen();
	void drawLevelScreen();
	void drawEndScreen();

public:
	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() const { return debug_mode; }
	void update();
	void draw();
	void init();
	unsigned int getWindowWidth() { return window_width; }
	unsigned int getWindowHeight() { return window_height; }
	float window2canvasX(float x);
	float window2canvasY(float y);
	void setWindowDimensions(unsigned int w, unsigned int h) { window_width = w; window_height = h; }
	Game();
	~Game();
};