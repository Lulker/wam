class TMX {
	std::vector<Sprite*> tileset;
	std::vector<int*> layers;
	Vector2<> last_camera;
	public:
		~TMX();
		/**
		* Loads map from a file
		* @param file name of the map file to load
		* @param offset number of characters to ignore in sprite path
		**/
		TMX(const char *file, const int &offset);
		///Tile size
		Vector2<int> tile;
		///Map size
		Vector2<int> map;
		/**
		* Renders map in screen
		* @param layer draw from to layer
		* @param center of the map (camera position)
		* @param radius of sight in tiles
		**/
		void camera(Vector2<int> layer, Vector2<> center, Vector2<> diameter){
			last_camera = center()(sub,diameter()(div,{2}));
			Vector2<int> m0(last_camera()(max,last_camera()(mul,{-1})));
			Vector2<int> me(last_camera()(add,diameter));
			//Vector2<int> px0(m0()(sub,Vector2<int>(m0))(mul,tile));
			//Vector2<int> pxe(px0()(add,diameter()(mul,tile)));
			//pxe(max,tile()(sub,{1})(add,GEK::screen()));
			for(int l=layer.x;l<layer.y;++l)
				for(int j=m0.y;j<me.y;++j)
					for(int i=m0.x;i<me.x;++i)
						tileset[layers[l][j*map.x+i]]->draw(tracecast({(double)i,(double)j}));
		};
		///Gets map position from screen position
		Vector2<> raycast(Vector2<> screen_position){return screen_position()(div,tile)(add,last_camera);}
		///Gets screen position from map position
		Vector2<> tracecast(Vector2<> map_position){return map_position()(sub,last_camera)(mul,tile);};
};
