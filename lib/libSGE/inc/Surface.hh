class Surface : public BCO {
	public:
		eK_Surface *surface;
		///Loads image from path as surface
		Surface(const char *path):surface(debug_assert(IMG_Load(path))){debug_var(path);}
		~Surface(){SDL_FreeSurface(surface);debug_point();}
};
