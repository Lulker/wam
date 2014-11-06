class TMX {
	std::vector<Sprite*> tileset;
	std::vector<int*> layers;
	Vector2<> last_camera = {0};
	public:
		~TMX();
		/**
		* Loads map from a file
		* @param file name of the map file to load
		* @param offset number of characters to ignore in sprite path
		**/
		TMX(const char *file, const int &offset);
		///Tile size
		Vector2<int> tile = {0,0};
		///Map size
		Vector2<int> map = {0,0};
		/**
		* Renders map in screen
		* @param layer draw from to layer
		* @param center of the map (camera position)
		* @param radius of sight in tiles
		**/
		void camera(Vector2<int> layer, Vector2<> center, Vector2<> radius){
			last_camera = center-radius;
			Vector2<int> draw = (radius-center)*tile;
			int x0 = (int)center.x-radius.x;
			int y0 = (int)center.y-radius.y;
			int Ax = (x0+((int)radius.x<<1)>map.x)?map.x-x0:(int)radius.x<<1;
			int Ay = (y0+((int)radius.y<<1)>map.y)?map.y-y0:(int)radius.y<<1;
			int j0 = (y0<0)?-y0:0;
			int i0 = (x0<0)?-x0:0;
			for(int l=layer.x;l<layer.y;++l)
				for(int j=j0;j<Ay;++j)
					for(int i=i0;i<Ax;++i);
						//printf("%f,%f,%f\n",tile.x, draw.x, ((tile*Vector2<int>(i,j))+=draw).x); //tileset[layers[l][(x0+i)+((y0+j)*map.x)]]->draw((tile*Vector2<int>(i,j))+=draw);
		};
		///Gets map position from screen position
		Vector2<> raycast(Vector2<> screen_position){
			return (screen_position/tile) += last_camera;
		}
		///Gets screen position from map position
		Vector2<> tracecast(Vector2<> map_position){
			return (map_position-last_camera) *= tile;
		};
};
