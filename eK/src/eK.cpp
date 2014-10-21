#include <eK.h>
#include <unistd.h>

eK::eK( const char *title )
{
	name = title;
	chdir(name);
	assert(!SDL_Init(SDL_INIT_EVERYTHING));
	assert(TTF_Init()!=-1);
	win = assert(SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_SHOWN|SDL_WINDOW_BORDERLESS|SDL_WINDOW_MAXIMIZED));
	ren = assert(SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
};

eK::~eK()
{
	if(ren)
		SDL_DestroyRenderer(ren);
	if(win)
		SDL_DestroyWindow(win);
	if(TTF_WasInit())
		TTF_Quit();
	SDL_Quit();
};

eK &eK::init( void(*init)(eK&) )
{
	init(*this);
	return *this;
};

int eK::loop( void(*draw)(eK&) )
{
	SDL_Event e;
	for(;;)
	{
		SDL_RenderClear(ren);
		while(SDL_PollEvent(&e))
			if(on[e.type])
				on[e.type](*this,e);
		draw(*this);
		SDL_RenderPresent(ren);
	}
};

eK &eK::bg( const int &&r, const int &&g, const int &&b )
{
	SDL_SetRenderDrawColor(ren, r, g, b, 255);
	return *this;
};

tSprite *eK::sprite(const char* file)
{
	return new tSprite(file,ren);
}
