class TMX {
	std::vector<Sprite*> tileset;
	std::vector<int*> layers;
	Vector2<double> last_camera = {0};
	public:
		~TMX();
		/**
		* Loads map from a file
		* @param file name of the map file to load
		* @param offset number of characters to ignore in sprite path
		**/
		TMX(const char *file, const int &offset);
		///Tile size
		Vector2<int> tile = {0};
		///Map size
		Vector2<int> map = {0};
		/**
		* Renders map in screen
		* @param layer0 the first layer to start drawing from
		* @param layer the last layer to draw
		* @param x horizontal position in map
		* @param y vertical position in map
		* @param Ax horizontal radius of sight
		* @param Ay vertical radius of sight
		**/
		void camera(int layer0, int layer, Vector2<double> center_position, Vector2<int> screen_size){/*
			float drawx = (x-(long)x)*-tilewidth;
			float drawy = (y-(long)y)*-tileheight;
			last_camera = Vector2(screen_size) /= 4; (Vector2(center_position) -= screen_size);
			yo = y-Ay;
			int x0 = ((long)x)-Ax;
			int y0 = ((long)y)-Ay;
			Vector2 top_left = Vector2<int>(center_position.x,center_position.y)
			Ax = (x0+(Ax<<1)>width)?width-x0:Ax<<1;
			Ay = (y0+(Ay<<1)>height)?height-y0:Ay<<1;
			for(int l=layer0;l<layer;++l)
				for(int j=(y0<0)?-y0:0;j<Ay;++j)
					for(int i=(x0<0)?-x0:0;i<Ax;++i)
						tileset[layers[l][(x0+i)+((y0+j)*width)]]->draw(drawx+(tilewidth*i),drawy+(tileheight*j));*/
		};
		///Gets map position from screen position
		auto raycast(const Vector2<double> screen_position){
			return (Vector2<double>(screen_position) /= tile) += last_camera;
		}
		///Gets screen position from map position
		auto tracecast(const Vector2<double> map_position){
			return (Vector2<double>(map_position) -= last_camera) *= tile;
		};
};
