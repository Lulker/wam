class Surface {
	public:
		eK_Surface *surface;
		///Loads image from path as surface
		Surface(const char *path):surface(assert(IMG_Load(path),snafu)){debug(snafu,path)}
		~Surface(){SDL_FreeSurface(surface);debug(snafu)}
};
