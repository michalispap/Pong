#include "game.h"
#include "graphics.h"
#include "config.h"
using namespace graphics;

void Game::spawnBall() {
	if (!ball && getKeyState(SCANCODE_SPACE)) {
		ball = new Ball(*this);
	}
}

void Game::checkBall() {
	if (ball && !ball->isActive()) {
		delete ball;
		ball = nullptr;
	}
}

bool Game::checkCollision() {
	if (!player || !ball || !player2) {
		return false;
	}

	Disk disk = ball->getCollisionHull();
	Rectangle rect = player->getCollisionHull2();
	Rectangle rect2 = player2->getCollisionHull2();

	//for first player
	if (disk.cx >= rect.cx && disk.cx <= rect.cx + rect.size1/2) {
		if (disk.cy >= rect.cy - rect.size2/2 && disk.cy <= rect.cy + rect.size2/2) {
			ball->changeDirection((cDir)((rand() % 3) + 4));
			playSound(std::string(ASSET_PATH) + "effect.mp3", 0.5f, false);
			return true;
		}
	}

	//for second player
	if (disk.cx <= rect2.cx && disk.cx >= rect2.cx - rect2.size1/2) {
		if (disk.cy >= rect2.cy - rect2.size2 / 2 && disk.cy <= rect2.cy + rect2.size2/2) {
			ball->changeDirection((cDir)((rand() % 3) + 1));
			playSound(std::string(ASSET_PATH) + "effect.mp3", 0.5f, false);
			return true;
		}
	}

	//left wall
	if (disk.cx < - 40.0f) {
		player2->increaseScore();
		updateEndScreen();
	}

	//right wall
	if (disk.cx > CANVAS_WIDTH + 40.0f) {
		player->increaseScore();
		updateEndScreen();
	}
	
	else
		return false;
}

void Game::updateStartScreen() {
	if (getKeyState(SCANCODE_RETURN)) {
		status = STATUS_PLAYING;
	}

	MouseState ms;
	getMouseState(ms);
	if (ms.button_left_pressed) {
		status = STATUS_PLAYING;
	}
}

void Game::updateLevelScreen() {
	if (!player_initialized && getGlobalTime() > 1000) {
		player = new Player(*this);
		player2 = new Player(*this);
		player_initialized = true;
		player->setPosX(20.0f);
		player2->setPosX(980.0f);
		player2->setPlayer(false);
		srand(time(NULL));
	}

	if (player)
		player->update();
	if (player2)
		player2->update();

	checkBall();
	spawnBall();

	if (ball)
		ball->update();

	if (checkCollision()) {
		ball->Move();
	};
	
}

void Game::updateEndScreen() {
	if (player->getScore() == end_score || player2->getScore() == end_score) {
		status = STATUS_FINISH;
	}
}

void Game::drawStartScreen() {
	Brush br;
	char info[40];
	sprintf_s(info, "Press ENTER or click to start");
	drawText(CANVAS_WIDTH / 4.5, CANVAS_HEIGHT / 3, 30, info, br);

	char infoButtons1[40];
	sprintf_s(infoButtons1, "-Player1: W (MoveUp)     S (MoveDown)");
	drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, 15, infoButtons1, br);

	char infoButtons2[45];
	sprintf_s(infoButtons2, "-Player2: I   (MoveUp)      K (MoveDown)");
	drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 1.75, 15, infoButtons2, br);

	char infoButtons3[40];
	sprintf_s(infoButtons3, "-Spawn   Ball: SPACE");
	drawText(CANVAS_WIDTH / 2.5, CANVAS_HEIGHT / 1.5, 15, infoButtons3, br);

	MouseState ms;
	getMouseState(ms);

	drawDisk(window2canvasX(ms.cur_pos_x), window2canvasY(ms.cur_pos_y), 10, br);
}

void Game::drawLevelScreen() {
	Brush br;
	br.texture = std::string(ASSET_PATH) + "background.png";
	br.outline_opacity = 0.0f;

	//draw background
	drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);

	//draw player
	if (player)
		player->draw();

	if (player2)
		player2->draw();

	if (ball)
		ball->draw();

	//UI/info layer
	if (player && player2 && debug_mode) {
		char info3[40];
		sprintf_s(info3, "Player 1's position: (%6.2f, %6.2f)", player->getPosX(), player->getPosY());
		drawText(50, 50, 15, info3, br);
		char info4[40];
		sprintf_s(info4, "Player 2's position: (%6.2f, %6.2f)", player2->getPosX(), player2->getPosY());
		drawText(650, 50, 15, info4, br);
	}

	if (player && player2) {
		char info1[40];
		sprintf_s(info1, "Player 1: %d", player->getScore());
		drawText(CANVAS_WIDTH / 2 - 75, 50, 15, info1, br);
		char info2[40];
		sprintf_s(info2, "Player 2: %d", player2->getScore());
		drawText(CANVAS_WIDTH / 2 - 75, 75, 15, info2, br);
	}

	if (getGlobalTime() > 60000) {
		char hardcore[40];
		sprintf_s(hardcore, "HARDCORE MODE ENABLED!");
		drawText(CANVAS_WIDTH / 2 - 125, 25, 15, hardcore, br);
	}

}

void Game::drawEndScreen() {
	Brush br;
	char infoEnd[40];
	char infoEndCongrats[40];
	if (player->getScore() == end_score) {
		sprintf_s(infoEnd, "Player 1 WINS!!!");
		drawText(CANVAS_WIDTH / 3.25, CANVAS_HEIGHT / 2, 40, infoEnd, br);
	}

	if (player2->getScore() == end_score) {
		sprintf_s(infoEnd, "Player 2 WINS!!!");
		drawText(CANVAS_WIDTH / 3.25, CANVAS_HEIGHT / 2, 40, infoEnd, br);
	}
	sprintf_s(infoEndCongrats, "Congratulations!");
	drawText(CANVAS_WIDTH / 3.75, CANVAS_HEIGHT / 3, 40, infoEndCongrats, br);
}

void Game::update() {
	if (status == STATUS_START) {
		updateStartScreen();
	}
	else if (status == STATUS_PLAYING) {
		updateLevelScreen();
	}
	else if (status == STATUS_FINISH) {
		updateEndScreen();
	}
}

void Game::draw() {
	if (status == STATUS_START) {
		drawStartScreen();
	}
	else if (status == STATUS_PLAYING) {
		drawLevelScreen();
	}
	else if (status == STATUS_FINISH) {
		drawEndScreen();
	}
}

void Game::init() {
	setFont(std::string(ASSET_PATH) + "bitstream.ttf");
	playMusic(std::string(ASSET_PATH) + "coffin_dance.mp3", 1.0f, true, 4000);
}

float Game::window2canvasX(float x) {
	return x * CANVAS_WIDTH / (float)window_width;
}

float Game::window2canvasY(float y) {
	return y * CANVAS_HEIGHT / (float)window_height;
}

Game::Game() {
}

Game::~Game() {
	if (player) {
		delete player;
	}
	if (player2) {
		delete player2;
	}
	if (ball) {
		delete ball;
	}
}
