class TMX : public BackCollector {
	std::vector<Sprite*> tileset;
	std::vector<int*> layers;
	Vector2 last_camera;
	public:
		~TMX();
		/**
		* Loads map from a file
		* @param file name of the map file to load
		* @param offset number of characters to ignore in sprite path
		**/
		TMX(const char *file, const int &offset);
		///Tile size
		Vector2 tile;
		///Map size
		Vector2 map;
		/**
		* Renders map in screen
		* @param layer draw from to layer
		* @param center of the map (camera position)
		* @param radius of sight in tiles
		**/
		void camera(int layer, const Vector2 &center, const Vector2 &diameter){
			last_camera = center - diameter/2;
			const Vector2 m0 = last_camera.clamp(0,map);
			const Vector2 me = (last_camera+diameter).clamp(0,map);
			for(int j=m0.y;j<=me.y;++j)
				for(int i=m0.x;i<=me.x;++i)
					tileset[layers[layer][i+j*(int)map.x]]->draw(tracecast(Vector2(i,j)));
		};
		///Gets map position from screen position
		Vector2 raycast(const Vector2 &screen_position)const{return (screen_position/tile)+last_camera;}
		///Gets screen position from map position
		Vector2 tracecast(const Vector2 &map_position)const{return (map_position-last_camera)*tile;};
};
