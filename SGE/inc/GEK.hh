struct Mouse {
	enum Button {NONE,L,M,LM,R,LR,RM,ANY} status;
	Vector2 position;
};

#define aspectratio GEK::screen.x/GEK::screen.y

class GEK {
	static void clean();
	public:
		static eK_Window *window;
		static eK_Renderer *renderer;
		///Scene that will run
		static Scene *scene;
		///Contains screen size
		static Vector2 screen;
		///Contains mouse position
		static Mouse mouse;
		///Sets background color
		static void bg(const int &red, const int &green, const int &blue){SDL_SetRenderDrawColor(renderer, red, green, blue, 255);};
		///Scene manager
		static int main(const char*, Scene*);
};
