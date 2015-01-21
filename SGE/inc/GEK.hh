#pragma once
#include "Scene.hh"
#include "Vector2.hh"
#include "Surface.hh"

struct Mouse {
	enum Button {NONE,L,M,LM,R,LR,RM,ANY} status;
	Button updated;
	Vector2 position;
};

#define aspectratio (GEK->screen.x/GEK->screen.y)

struct GameEngineKernel {
	///Window instance
	eK_Window *window;
	///Renderer instance
	eK_Renderer *renderer;
	///Contains font
	eK_TTF font;
	///Server that we will try to connect
	const char *server;
	///Scene that will run
	Scene *scene;
	///Contains screen size
	Vector2 screen;
	///Contains mouse position
	Mouse mouse;
	///Singleton
	GameEngineKernel(const char* title, const char* ip = "127.0.0.1"):server(ip),scene(0),mouse({Mouse::NONE,Mouse::NONE,{0,0}}){
		assert(!SDL_Init(eK_INIT_EVERYTHING));
		eK_DisplayMode info;
		assert(!SDL_GetCurrentDisplayMode(0,&info));
		screen = Vector2(info.w,info.h);
		window = assert(SDL_CreateWindow(title, eK_WINDOWPOS_CENTERED, eK_WINDOWPOS_CENTERED, info.w, info.h, eK_WINDOW_SHOWN|eK_WINDOW_BORDERLESS|eK_WINDOW_MAXIMIZED));
		renderer = assert(SDL_CreateRenderer(window, -1, eK_RENDERER_ACCELERATED | eK_RENDERER_PRESENTVSYNC));
		assert(!TTF_Init());
		font = TTF_OpenFont("fonts/FiraSans-Light.ttf", 18);
	}
	int loop(Scene* initial_scene){
		scene = initial_scene;
		for(Scene *cs;(cs = scene);delete cs)
			for(int x,y; cs==scene;){
				eK_Event e;
				SDL_RenderClear(renderer);
				while(SDL_PollEvent(&e))
					switch(e.type){
						case eK_WINDOWEVENT:
							SDL_GetWindowSize(window,&x,&y);
							screen = Vector2(x,y);
						break;
						case eK_QUIT:return 0;
						default:if(cs->on.count(e.type))
							cs->on[e.type](e);
					}
				Mouse::Button previous = mouse.status;
				mouse = {(Mouse::Button)(SDL_GetMouseState(&x,&y) & Mouse::ANY),(Mouse::Button)0,Vector2(x,y)};
				mouse.updated = Mouse::Button(previous^mouse.status);
				scene = (*cs)();
				SDL_RenderPresent(renderer);
			}
		return 0;
	}
	~GameEngineKernel(){
		if(scene) delete scene;
		if(renderer) SDL_DestroyRenderer(renderer);
		if(window) SDL_DestroyWindow(window);
		if(TTF_WasInit()) TTF_Quit();
		SDL_Quit();
	}
	///Sets background color
	void bg(const int &red, const int &green, const int &blue){SDL_SetRenderDrawColor(renderer, red, green, blue, 255);};
};

extern GameEngineKernel *GEK;
