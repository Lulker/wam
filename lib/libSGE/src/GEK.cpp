#include <SGE.hpp>
#include <cstdlib>
#include <chrono>

void SGE::GEK::clean(){
	if(scene)
		scene->quit();
	if(renderer)
		SDL_DestroyRenderer(renderer);
	if(window)
		SDL_DestroyWindow(window);
	if(TTF_WasInit())
		TTF_Quit();
	SDL_Quit();
}

int SGE::GEK::main(const char *title, Scene *initial_scene){
	assert(SDL_Init(eK_INIT_EVERYTHING),!=0);
	assert(TTF_Init(),!=-1);
	renderer = window = assert(SDL_CreateWindow(title, eK_WINDOWPOS_CENTERED, eK_WINDOWPOS_CENTERED, 0, 0, eK_WINDOW_SHOWN|eK_WINDOW_BORDERLESS|eK_WINDOW_MAXIMIZED));
	renderer = assert(SDL_CreateRenderer(window, -1, eK_RENDERER_ACCELERATED | eK_RENDERER_PRESENTVSYNC));
	scene = initial_scene;
	atexit(clean);
	while(scene){
		Scene *cs = scene;
		scene->init();
		eK_Event e;
		auto t = std::chrono::high_resolution_clock::now();
		while(cs==scene){
			auto tmp = t;
			SDL_RenderClear(renderer);
			while(SDL_PollEvent(&e))
				switch(e.type){
					case eK_WINDOWEVENT:
						SDL_GetWindowSize(window,&screen.x,&screen.y);break;
					case eK_QUIT:
						exit(0);break;
					default:if(cs->on[e.type])
						cs->on[e.type](e);
				}
			cs->loop((std::chrono::duration_cast<std::chrono::duration<double>>((t = std::chrono::high_resolution_clock::now())-tmp)).count());
			SDL_RenderPresent(renderer);
		}
		cs->quit();
	}
	exit(0);
	return 0;
}
