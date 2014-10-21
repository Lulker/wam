#include <eK.h>
#include <cmwc.h>
#include <vector>
#include <ctime>
#include <functional>
#define rand prng.rand

std::vector<tSprite*> sprites;

void draw(eK & ge)
{
	sprites[0]->draw( 0,0 );
};

void init(eK & ge)
{
	sprites.reserve(100);
	sprites[0] = ge.sprite("gfx/character.bmp");
	ge.on[SDL_QUIT] = [](eK & ge,SDL_Event & e){exit(0);};
	ge.on[SDL_KEYDOWN] = [](eK & ge,SDL_Event & e){
		switch(e.key.keysym.sym){
			case SDLK_w:

				break;
		};
	};
/*
	ge.on[SDL_KEYUP] = [](eK& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_MOUSEMOTION] = [](eK& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_MOUSEBUTTONDOWN] = [](eK& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_MOUSEBUTTONUP] = [](eK& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_DROPFILE] = [](eK& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_MOUSEWHEEL] = [](eK& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_DROPFILE] = [](eK& ge,SDL_Event& e){exit(0);};
*/
};

#ifdef __WIN32
#include <windows.h>

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	std::string name(GetCommandLine());
	*(&name[0] + name.find_last_of(".")) = 0;
	const char * program = &name[0] + 1 + name.find_last_of("\\");
#else
int main(int argc, char const *argv[])
{
	const char * program = argv[0];
#endif
	cmwc prng(time(0));
	return eK(program).init(init).loop(draw);
}
