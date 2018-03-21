#include "Game.h"
#include "HanioTowerAlgo.h"

Game::Game(int level) {
	this->HanioTowerLevel = level;
	//this->HanioTowerSolution = solu;//出现越界错误
	this->HanioTowerSolution = vector<int>(this->CalculateSolution(level));
}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	this->WindowWidth = width; this->WindowHeight = height;
	this->FullRect.x = this->FullRect.y = 0; 
	this->FullRect.w = width; this->FullRect.h = height;
	this->pillar_x[0] = width * 0.25; this->pillar_x[1] = width * 0.5; this->pillar_x[2] = width * 0.75;
	this->pillar_max_height = height * 0.666; this->pillar_max_width = width / 50;
	this->sheet_max_width = width * 0.25; this->sheet_max_height = this->pillar_max_height / this->HanioTowerLevel / 2;

	for (i = 0; i < this->HanioTowerLevel; i++) {
		SDL_Rect *rct = new SDL_Rect();
		rct->w = pow(0.666, i + 1)*this->sheet_max_width;
		rct->h = this->sheet_max_height;
		rct->x = this->pillar_x[0] - rct->w / 2;
		rct->y = this->WindowHeight - (i + 1) * this->sheet_max_height;

		this->pillar_sheet[0].push_back(rct);
	}
	for (i = 0; i < 3; i++) {
		SDL_Rect *rct = new SDL_Rect();
		rct->x = this->pillar_x[i] - this->pillar_max_width / 2;
		rct->y = this->WindowHeight - this->pillar_max_height;
		rct->w = this->pillar_max_width;
		rct->h = this->pillar_max_height;

		this->pillarR.push_back(rct);
	}

	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		logd("Subsystem Initialised!...");

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			logd("Window created!");
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			logd("Renderer created!");
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	this->FullTexture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TextureAccess::SDL_TEXTUREACCESS_TARGET, width, height);
}
void Game::handleEvent() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_s) {
			this->start_move_sheet();
			logd("Game::handleEvent(): start_move");
		}
		break;
	case SDL_FINGERDOWN:
		this->start_move_sheet();
		break;
	default:
		break;
	}
}
void Game::update() {
	while (true == this->isPaused) {
		//为了避免冲突
	}
	if (this->cur_move_from >= 0 && this->move_all_end == false) {
		if (false == this->is_moving) {
			this->is_moving = true;
			logd("Game::update: call move_sheet(%d, %d)", this->HanioTowerSolution[this->cur_move_from], this->HanioTowerSolution[this->cur_move_to]);
			move_sheet(this->HanioTowerSolution[this->cur_move_from], this->HanioTowerSolution[this->cur_move_to]);
		}
	}

	//绘制三个石柱
	SDL_SetRenderTarget(this->renderer, this->FullTexture);
	SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0x00);//黑色
	//清空整个纹理为全黑
	SDL_RenderDrawRect(this->renderer, &this->FullRect);
	SDL_RenderFillRect(this->renderer, &this->FullRect);
	SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0xff, 0x00);//蓝色
	for (i = 0; i < this->pillarR.size(); i++) {
		SDL_RenderDrawRect(this->renderer, pillarR[i]);
		SDL_RenderFillRect(this->renderer, pillarR[i]);
	}

	SDL_SetRenderDrawColor(this->renderer, 0xff, 0x00, 0x00, 0x00);//红色
	for (i = 0; i < 3; i++) {
		for (j = 0; j < this->pillar_sheet[i].size(); j++) {
			SDL_RenderDrawRect(this->renderer, pillar_sheet[i][j]);
			SDL_RenderFillRect(this->renderer, pillar_sheet[i][j]);
		}
	}

	//SDL_SetRenderDrawColor(this->renderer, 0x00, 0xff, 0x00, 0x00);//绿色
	SDL_SetRenderTarget(this->renderer, NULL);

	check_move_step_end();

	if (this->start_move == true && this->move_all_end == false) {
		if (this->is_moving == false) {
			//(cur_move_from < ((this->HanioTowerSolution.size()) - 2)) = 0奇葩错误又出现了2018/3/18/20/07
			//增加中间变量int t之后，条件判断才终于正确，大概size_t和int两个类型的比较有问题
			//logd("cur_move_from - ((this->HanioTowerSolution.size()) - 2) = %d", cur_move_from - ((this->HanioTowerSolution.size()) - 2));
			int t = cur_move_from - ((this->HanioTowerSolution.size()) - 2);
			if (t < 0) {
				logd("************************");
				this->cur_move_from += 2;
				this->cur_move_to += 2;
			}
			else {
				this->move_all_end = true;
			}
		}
	}
}
void Game::render() {
	SDL_RenderClear(renderer);
	//这样的话，背景是绿色
	/*for (i = 0; i < pillarR.size(); i++) {
		SDL_RenderCopy(renderer, FullTexture, pillarR[i], pillarR[i]);
	}
	for (j = 0; j < 3; j++) {
		for (i = 0; i < pillar_sheet[j].size(); i++) {
			SDL_RenderCopy(renderer, FullTexture, pillar_sheet[j][i], pillar_sheet[j][i]);
		}
	}*/
	SDL_RenderCopy(renderer, FullTexture, NULL, NULL);//这样的话，背景是黑色

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	logd("Game cleaned!");
}

void Game::move_sheet(int f, int t) {
	this->is_moving = true;
	this->move_step_process = 1;
	SDL_Rect * rct;

	if (f < t) {
		this->delta_x = this->speed_move;
	}
	else {
		this->delta_x = -this->speed_move;
	}
	rct = pillar_sheet[f - 1].back();
	pillar_sheet[f - 1].pop_back();

	//rct->x = this->pillar_x[t - 1] - rct->w / 2;
	//rct->y = this->WindowHeight - (pillar_sheet[t - 1].size() + 1) * this->sheet_max_height;
	this->move_step_end_at_x = this->pillar_x[t - 1] - rct->w / 2;
	this->move_step_end_at_y = this->WindowHeight - (pillar_sheet[t - 1].size() + 1) * this->sheet_max_height;
	pillar_sheet[t - 1].push_back(rct);

	this->rect_move_cur = rct;
}

void Game::check_move_step_end() {
	if (this->is_moving == true) {
		switch (this->move_step_process) {
		case 1:
			this->delta_y = -this->speed_move;
			this->rect_move_cur->y += this->delta_y;
			if (this->rect_move_cur->y <= this->WindowHeight - (this->pillar_max_height+this->sheet_max_height)) {
				this->rect_move_cur->y = this->WindowHeight - (this->pillar_max_height + this->sheet_max_height);
				this->move_step_process = 2;
			}
			break;
		case 2:
			this->delta_x = this->delta_x;
			this->rect_move_cur->x += this->delta_x;
			if (this->delta_x > 0) {
				if (this->rect_move_cur->x >= this->move_step_end_at_x) {
					this->rect_move_cur->x = this->move_step_end_at_x;
					this->move_step_process = 3;
				}
			}
			else {
				if (this->rect_move_cur->x <= this->move_step_end_at_x) {
					this->rect_move_cur->x = this->move_step_end_at_x;
					this->move_step_process = 3;
				}
			}
			break;
		case 3:
			this->delta_y = this->speed_move;
			this->rect_move_cur->y += this->delta_y;
			if (this->rect_move_cur->y >= this->move_step_end_at_y) {
				this->rect_move_cur->y = this->move_step_end_at_y;
				this->move_step_process = 1;

				this->is_moving = false;
			}
			break;
		default:
			break;
		}
	}
}

vector<int> Game::CalculateSolution(int level) {
	int i;

	HanioTowerAlgo *hanio = new HanioTowerAlgo(level);
	return hanio->GetSolution();	
}

void Game::changeHanioTowerLevel(int level) {
	this->HanioTowerLevel = level;
	this->HanioTowerSolution = vector<int>(this->CalculateSolution(level));

	for (i = 0; i < 3; i++) {
		int tmp = this->pillar_sheet[i].size();
		for (j = 0; j < tmp; j++) {
			delete this->pillar_sheet[i].back();//回收内存
			this->pillar_sheet[i].pop_back();
		}
	}
	this->sheet_max_height = this->pillar_max_height / this->HanioTowerLevel / 2;
	for (i = 0; i < this->HanioTowerLevel; i++) {
		SDL_Rect *rct = new SDL_Rect();
		rct->w = pow(0.666, i + 1)*this->sheet_max_width;
		rct->h = this->sheet_max_height;
		rct->x = this->pillar_x[0] - rct->w / 2;
		rct->y = this->WindowHeight - (i + 1) * this->sheet_max_height;

		this->pillar_sheet[0].push_back(rct);
	}

	this->cur_move_from = -2; this->cur_move_to = -1;	
	this->start_move = false;
	this->is_moving = false;
	this->move_all_end = false;
	this->move_step_process = 1;

	this->isPaused = false;
}
