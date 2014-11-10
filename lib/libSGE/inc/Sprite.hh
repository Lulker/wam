class Sprite : public BCO {
	eK_Texture *texture;
	eK_Rect destination;
	public:
		///Uses surface as sprite
		Sprite(const Surface surface):texture(debug_assert(SDL_CreateTextureFromSurface(GEK::renderer, surface.surface))){
			debug_point();
			SDL_QueryTexture(texture, 0, 0, &destination.w, &destination.h);
		}
		~Sprite(){
			SDL_DestroyTexture(texture);
			debug_point();
		}
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
		}
		void draw(int x, int y, const double &angle = 0, eK_RendererFlip flip = 0){
			destination.x = x;
			destination.y = y;
			SDL_RenderCopyEx(GEK::renderer, texture, 0, &destination, angle, 0, flip);
		}
};
