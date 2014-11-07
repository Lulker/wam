#include <SGE.hpp>
#include <chrono>

using namespace SGE;

eK_Window *GEK::window = 0;
eK_Renderer *GEK::renderer = 0;
Scene *GEK::scene = 0;
Vector2<> GEK::screen(0);

void GEK::clean(){
	debug(snafu);
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

void GEK::main(const char *title, Scene *initial_scene){
	assert(!SDL_Init(eK_INIT_EVERYTHING),snafu);
	assert(!TTF_Init(),snafu);
	assert(renderer = window = SDL_CreateWindow(title, eK_WINDOWPOS_CENTERED, eK_WINDOWPOS_CENTERED, 0, 0, eK_WINDOW_SHOWN|eK_WINDOW_BORDERLESS|eK_WINDOW_MAXIMIZED),snafu);
	assert(renderer = SDL_CreateRenderer(window, -1, eK_RENDERER_ACCELERATED | eK_RENDERER_PRESENTVSYNC),snafu);
	scene = initial_scene;
	atexit(clean);
	for(;;){
		Scene *cs = scene;
		scene->init();
		eK_Event e;
		auto t = std::chrono::high_resolution_clock::now();
		int x,y;
		while(cs==scene){
			auto tmp = t;
			SDL_RenderClear(renderer);
			while(SDL_PollEvent(&e))
				switch(e.type){
					case eK_WINDOWEVENT:
						SDL_GetWindowSize(window,&x,&y);
						screen={(double)x,(double)y};
					break;
					case eK_QUIT:
						std::exit(0);
					default:if(cs->on[e.type])
						cs->on[e.type](e);
				}
			cs->loop((std::chrono::duration_cast<std::chrono::duration<double>>((t = std::chrono::high_resolution_clock::now())-tmp)).count());
			SDL_RenderPresent(renderer);
		}
		cs->quit();
	}
}
