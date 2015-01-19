#pragma once
#include "Sprite.hh"
class TMX : public BackCollector {
	std::vector<Sprite*> tileset;
	std::vector<int*> layers;
	Vector2 last_camera;
	int mapw;
	void fovx(const int draw, const int x, const int y, const int Ax, const int radius) {
		if(!radius) return;
		if(operator()(draw,x,y)>=0)
			tileset[operator()(draw,x,y)]->draw(tracecast(Vector2(x,y)));
		if(operator()(1,x,y)!=-1) return;
		fovx(draw,x+Ax,y,Ax,radius-1);
	};

	void fovy(const int draw, const int x, const int y, const int Ay, const int radius) {
		if(!radius) return;
		if(operator()(draw,x,y)>=0)
			tileset[operator()(draw,x,y)]->draw(tracecast(Vector2(x,y)));
		if(operator()(1,x,y)!=-1) return;
		fovy(draw,x,y+Ay,Ay,radius-1);
	}

	void fovxy(const int draw, const int x,const int y,const int Ax,const int Ay,const int radius) {
		if(!radius) return;
		if(operator()(draw,x,y)>=0)
			tileset[operator()(draw,x,y)]->draw(tracecast(Vector2(x,y)));
		if(operator()(1,x,y)!=-1) return;
		fovx(draw,x+Ax,y+Ay,Ax,radius-1);
		fovy(draw,x+Ax,y+Ay,Ay,radius-1);
		fovxy(draw,x+Ax,y+Ay,Ax,Ay,radius-1);
	}
	void fov(const int draw, const int x, const int y, const int radius) {
		mapw = (int)map.x;
		fovx(draw,x,y,-1,radius-1);
		fovy(draw,x,y,-1,radius-1);
		fovx(draw,x,y,1,radius-1);
		fovy(draw,x,y,1,radius-1);
		fovxy(draw,x,y,-1,-1,radius-1);
		fovxy(draw,x,y,1,-1,radius-1);
		fovxy(draw,x,y,1,1,radius-1);
		fovxy(draw,x,y,-1,1,radius-1);
	}
	public:
		const int& operator()(const int layer, const int x, const int y){return layers[layer][x+y*mapw];}
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
		* Renders map in screen in O(n) time, with as few cache misses as possible
		* @param layer draw from to layer
		* @param center of the map (camera position)
		* @param radius of sight in tiles
		**/
		void camera(const int layer, const Vector2 &center, const Vector2 &diameter){
			last_camera = center - diameter/2;
			for(auto sprite:tileset)
				sprite->setAlpha(0.5*255);
			const Vector2 m0 = last_camera.clamp(0,map-1);
			const Vector2 me = (last_camera+diameter).clamp(0,map-1);
			for(int j=m0.y;j<=me.y;++j)
				for(int i=m0.x;i<=me.x;++i)
					if(layers[layer][i+j*(int)map.x]>=0)
						tileset[layers[layer][i+j*(int)map.x]]->draw(tracecast(Vector2(i,j)));
			for(auto sprite:tileset)
				sprite->setAlpha(1*255);
			fov(layer,center.x,center.y,9);
		};
		///Gets map position from screen position
		Vector2 raycast(const Vector2 &screen_position)const{return (screen_position/tile)+last_camera;}
		///Gets screen position from map position
		Vector2 tracecast(const Vector2 &map_position)const{return (map_position-last_camera)*tile;};
};
