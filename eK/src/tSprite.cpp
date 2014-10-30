#include <eK.hpp>
#include <SDL_image.h>

tSprite::tSprite(const char *file, SDL_Renderer *renderer){
	ren = renderer;
	SDL_Surface *img = assert(IMG_Load(file));
	tex = assert(SDL_CreateTextureFromSurface(ren, img));
	SDL_FreeSurface(img);
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
}

void tSprite::draw(int x, int y){
	dst.x = x;
	dst.y = y;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

tObject *tSprite::object(float x, float y, float speed){
	return new tObject(this,x,y,speed);
}
