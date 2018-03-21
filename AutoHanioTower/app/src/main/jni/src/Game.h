#pragma once
#include <SDL.h>
#include "log.h"
#include <vector>
#include <math.h>
using namespace std;

/*
用于调试
*/
extern void changeHanioLevel(int lev);
extern void changeFPS(int f);
extern void startMove();

class Game {
public:
	Game(int level);
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvent();
	void update();
	void render();
	void clean();
	bool running() {
		return isRunning;
	}
	void start_move_sheet() {//如果函数名与变量重名，会优先引用函数
		this->start_move = true;
	}
	void closeGame() {
		this->isRunning = false;
	}
	void changeHanioTowerLevel(int lev);
	
private:
	int WindowWidth = 0, WindowHeight = 0;
	int i = 0, j = 0, k = 0;
	bool isRunning = false;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *FullTexture = NULL;
	SDL_Rect FullRect;
	vector<SDL_Rect*> srcR, destR, pillarR;

	int HanioTowerLevel = 1;
	vector<int> HanioTowerSolution;
	int sheet_max_height = 0;
	int sheet_max_width = 0;
	int pillar_max_height = 0;
	int pillar_max_width = 0;
	int pillar_x[3] = { 0 };
	//vector<SDL_Rect*> pillar_sheet1, pillar_sheet2, pillar_sheet3;//存放每个柱子上的圆盘
	vector<SDL_Rect*> pillar_sheet[3];

	int cur_move_from = -2, cur_move_to = -1;//当前从cur_move1移动到cur_move2
	//bool move_step_end = true;
	//bool move_step_start = false;
	bool isPaused = false;
	bool start_move = false;
	bool is_moving = false;
	bool move_all_end = false;
	int move_step_process = 1;//1,2,3分别代表拉起，横向移动，放下，三个过程
	SDL_Rect *rect_move_cur;

	int delta_x = 0, delta_y = 0;
	int speed_move = 20;
	int move_step_end_at_x = 0, move_step_end_at_y = 0;	

	void move_sheet(int f, int t);
	void check_move_step_end();
	vector<int> CalculateSolution(int level);
};