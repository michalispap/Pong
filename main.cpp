#include "graphics.h"
#include "game.h"
#include "config.h"
using namespace graphics;

void resize(int w, int h) {
    Game* game = reinterpret_cast<Game*>(getUserData());
    game->setWindowDimensions((unsigned int)w, (unsigned int)h);
}


void update(float ms) {
    Game * game = reinterpret_cast<Game *>(getUserData());
    game->update();
}

void draw() {
    Game* game = reinterpret_cast<Game*>(getUserData());
    game->draw();
}

int main() {

    Game mygame;

    createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong Game");

    setUserData(&mygame);

    setDrawFunction(draw);
    setUpdateFunction(update);

    setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    mygame.init();
    mygame.setDebugMode(false); //Set "true" for debug mode
    startMessageLoop();

    return 0;
}
