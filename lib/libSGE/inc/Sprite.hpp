class Sprite {
	eK_Texture *texture;
	eK_Rect destination;
	public:
		///Uses surface as sprite
		Sprite(Surface &&surface){
			assert(texture = SDL_CreateTextureFromSurface(GEK::renderer, surface.surface),snafu);
			SDL_QueryTexture(texture, 0, 0, &destination.w, &destination.h);
		debug(snafu)};
		Sprite(Surface *&&surface){
			assert(texture = SDL_CreateTextureFromSurface(GEK::renderer, surface->surface),snafu);
			SDL_QueryTexture(texture, 0, 0, &destination.w, &destination.h);
			delete surface;
		debug(snafu)};
		Sprite(Surface *&surface):Sprite(std::move(*surface)){};
		~Sprite(){SDL_DestroyTexture(texture);debug(snafu)};
		/**
		* Draws sprite in a position of the screen
		* @param x horizontal position in screen
		* @param y vertical position in screen
		* @param angle optional angle to rotate sprite
		* @param flip optional parameter to flip sprite
		**/
		void draw(const Vector2<> &position = {0,0}, const double &angle = 0, eK_RendererFlip flip = 0){
			destination.x = position.x;
			destination.y = position.y;
			SDL_RenderCopyEx(GEK::renderer, texture, 0, &destination, angle, 0, flip);
		};
};
