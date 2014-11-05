class Surface {
	public:
		eK_Surface *surface;
		///Loads image from path as surface
		Surface(const char *path):surface(assert(IMG_Load(path))){};
		~Surface(){SDL_FreeSurface(surface);};
};