#include <eK.h>
#include <iterator>

tSprite::tSprite( const char *file, SDL_Renderer *renderer )
{
	ren = renderer;
	SDL_Surface *img = assert(IMG_Load(file));
	tex = assert(SDL_CreateTextureFromSurface(ren, img));
	SDL_FreeSurface(img);
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
}

tSprite::tSprite( SDL_Texture *texture )
{
	tex = texture;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
}

tSprite &tSprite::draw( int x, int y )
{
	int j = dst.x;
	int k = dst.y;
	dst.x = x;
	dst.y = y;
	SDL_RenderCopy(ren, tex, NULL, &dst);
	dst.x = j;
	dst.y = k;
	return *this;
}

tSprite &tSprite::drawarray(auto & CL)
{
	auto end_it = std::end(CL);
	int j = dst.x;
	int k = dst.y;
	for (auto i = std::begin(CL); i != end_it; ++i)
	{
		dst.x = i.first;
		dst.y = i.second;
		SDL_RenderCopy(ren, tex, NULL, &dst);
	}
	dst.x = j;
	dst.y = k;
	return *this;
}
