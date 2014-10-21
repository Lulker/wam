#include <e2D.h>
#include <cmwc.h>
#include <vector>
#include <ctime>
#include <functional>
#define rand prng.rand

std::vector<tSprite*> sprites;

void draw(e2D &ge)
{
	sprites[0]->draw( 0,0 );
};

void init(e2D &ge)
{
	sprites.reserve(100);
	sprites[0] = ge.sprite("gfx/character.bmp");
	ge.on[SDL_QUIT] = [](e2D& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_KEYDOWN] = [](e2D& ge,SDL_Event& e){
		switch(e.key.keysym.sym){
			case SDLK_w:

				break;
		};
	};
/*
	ge.on[SDL_KEYUP] = [](e2D& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_MOUSEMOTION] = [](e2D& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_MOUSEBUTTONDOWN] = [](e2D& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_MOUSEBUTTONUP] = [](e2D& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_DROPFILE] = [](e2D& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_MOUSEWHEEL] = [](e2D& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_DROPFILE] = [](e2D& ge,SDL_Event& e){exit(0);};
*/
};

#include <windows.h>

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	cmwc prng(time(0));
	std::string name(GetCommandLine());
	*(&name[0] + name.find_last_of(".")) = 0;
	const char *program = &name[0] + 1 + name.find_last_of("\\");
	return e2D(program).init(init).loop(draw);
}
