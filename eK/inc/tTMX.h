#pragma once
#include <eK.h>

class tTMX
{
  private:
    std::vector<tSprite*> tileset;
    std::vector<int*> layers;
  public:
    int tilewidth;
    int tileheight;
    int width;
    int height;
    int size;
    tTMX( const char * filename, SDL_Renderer * ren , const int & offset );
    void draw(int layer, int x0, int x, int y0, int y, float drawx0, float drawy0);
};
