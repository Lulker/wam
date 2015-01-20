#include "GEK.hh"
#include <chrono>

eK_Window *GEK::window = 0;
eK_Renderer *GEK::renderer = 0;
const char *GEK::server = 0;
Scene *GEK::scene = 0;
struct Mouse GEK::mouse = {Mouse::NONE,(Mouse::Button)0,{0,0}};
Vector2 GEK::screen(0);

void GEK::clean(){
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

int GEK::main(const char *title, Scene *initial_scene){
	assert(!SDL_Init(eK_INIT_EVERYTHING));
	assert(!TTF_Init());
	assert(renderer = window = SDL_CreateWindow(title, eK_WINDOWPOS_CENTERED, eK_WINDOWPOS_CENTERED, 0, 0, eK_WINDOW_SHOWN|eK_WINDOW_BORDERLESS|eK_WINDOW_MAXIMIZED));
	assert(renderer = SDL_CreateRenderer(window, -1, eK_RENDERER_ACCELERATED | eK_RENDERER_PRESENTVSYNC));
	//TODO: font = TTF_OpenFont("fonts/FiraSans-Light.ttf", 18);
	scene = initial_scene;
	atexit(clean);
	for(;;){
		Scene *cs = scene;
		scene->init();
		int x,y;
		eK_Event e;
		std::chrono::system_clock::time_point tmp, t = std::chrono::high_resolution_clock::now();
		while(cs==scene){
			tmp = t;
			SDL_RenderClear(renderer);
			while(SDL_PollEvent(&e))
				switch(e.type){
					case eK_WINDOWEVENT:
						SDL_GetWindowSize(window,&x,&y);
						screen = Vector2(x,y);
					break;
					case eK_QUIT:
						std::exit(0);
					default:if(cs->on.count(e.type))
						cs->on[e.type](e);
				}
			Mouse::Button previous = mouse.status;
			mouse = {(Mouse::Button)(SDL_GetMouseState(&x,&y) & Mouse::ANY),(Mouse::Button)0,Vector2(x,y)};
			mouse.updated = Mouse::Button(previous^mouse.status);
			cs->loop((std::chrono::duration_cast<std::chrono::duration<double>>((t = std::chrono::high_resolution_clock::now())-tmp)).count());
			SDL_RenderPresent(renderer);
		}
		cs->quit();
	}
}
