//
// Created by asus on 2018/3/21.
//
#include "entry.h"
#include "log.h"
#include "HanioTowerAlgo.h"
#include "Game.h"
#include <jni.h>
#include "org_libsdl_app_CallNativeMethods.h"

int level = 3;
int FPS = 50;
Game *game = NULL;

extern "C"
JNIEXPORT void JNICALL Java_org_libsdl_app_CallNativeMethods_changeHanioLevel(JNIEnv *env, jclass jobj, jint lev)
{
    logd("I am in jni");
    level = lev;
    game->changeHanioTowerLevel(level);
}
extern "C"
JNIEXPORT void JNICALL Java_org_libsdl_app_CallNativeMethods_changeFPS(JNIEnv *env, jclass jobj, jint f)
{
    FPS = f;
}
extern "C"
JNIEXPORT void JNICALL Java_org_libsdl_app_CallNativeMethods_startMove(JNIEnv *env, jclass jobj)
{
    game->start_move_sheet();
}


extern "C"
int entry(int argc, char* argv[]){
    int frameDelay;

	int frameStart;
	int frameTime;

	game = new Game(level);
	game->init("AutoHanioTower", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	while (game->running()) {
		frameDelay = 1000 / FPS;

		frameStart = SDL_GetTicks();

		game->handleEvent();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game->clean();

	return 0;
}
