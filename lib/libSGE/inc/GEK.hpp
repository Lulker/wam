class GEK {
	static void clean();
	public:
		static eK_Window *window;
		static eK_Renderer *renderer;
		///Scene that will run
		static Scene *scene;
		///Contains screen size
		static Vector2<int> screen;
		///Sets background color
		static void bg(const int &red, const int &green, const int &blue){SDL_SetRenderDrawColor(renderer, red, green, blue, 255);};
		///Scene manager
		static void main(const char*, Scene*);
};
