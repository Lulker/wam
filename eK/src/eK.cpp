#include <eK.hpp>
#include <SDL_ttf.h>

eK::eK(const char *title){
	eDBG_INIT
	assert(!SDL_Init(SDL_INIT_EVERYTHING));
	assert(TTF_Init()!=-1);
	win = assert(SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_SHOWN|SDL_WINDOW_BORDERLESS|SDL_WINDOW_MAXIMIZED));
	ren = assert(SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	SDL_GetWindowSize(win,&width,&height);
}

eK::~eK(){
	if(ren)
		SDL_DestroyRenderer(ren);
	if(win)
		SDL_DestroyWindow(win);
	if(TTF_WasInit())
		TTF_Quit();
	SDL_Quit();
}

void eK::bg(const int &r, const int &g, const int &b){
	SDL_SetRenderDrawColor(ren, r, g, b, 255);
}

tSprite *eK::sprite(const char *file){
	return new tSprite(file,ren);
}

tTMX *eK::tmx(const char *file, const int &offset){
	return new tTMX(file,*this,offset);
}

int eK::main(){
	while(scene){
		scene->on[SDL_QUIT] = [](SDL_Event & e){game_engine->exit(0);};
		scene->init();
		SDL_Event e;
		tScene *cs = scene;
		do{
			SDL_RenderClear(ren);
			while(SDL_PollEvent(&e))
				if(cs->on[e.type])
					cs->on[e.type](e);
			SDL_RenderPresent(ren);
			cs->loop();
		} while(cs==scene);
		cs->quit();
	}
	return ret;
}

void eK::exit(const int &code){
	scene = 0;
	ret = code;
	delete this;
}
