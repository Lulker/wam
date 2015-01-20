#pragma once
#include "Vector2.hh"
#include <vector>
struct Map {
    std::vector<int*> layers;
    void fovx(std::vector<Vector2>& visibles, const int x, const int y, const int Ax, const int radius)const{
        if(radius<0) return;
        if(operator()(x,y)!=-1) return;
        visibles.push_back(Vector2(x,y));
        fovx(visibles,x+Ax,y,Ax,radius-1);
    };

    void fovy(std::vector<Vector2>& visibles, const int x, const int y, const int Ay, const int radius)const{
        if(radius<0) return;
        if(operator()(x,y)!=-1) return;
        visibles.push_back(Vector2(x,y));
        fovy(visibles,x,y+Ay,Ay,radius-1);
    }

    void fovxy(std::vector<Vector2>& visibles, const int x,const int y,const int Ax,const int Ay,const int radiusx, const int radiusy)const{
        if(radiusx<0 && radiusy<0) return;
        if(operator()(x,y)!=-1) return;
        visibles.push_back(Vector2(x,y));
        fovx(visibles,x+Ax,y+Ay,Ax,radiusx-1);
        fovy(visibles,x+Ax,y+Ay,Ay,radiusy-1);
        fovxy(visibles,x+Ax,y+Ay,Ax,Ay,radiusx-2,radiusy-2);
    }
    void fov(std::vector<Vector2>& visibles, const int x, const int y, const int radius)const{
        fovy(visibles,x,y,-1,radius-1);
        fovx(visibles,x,y,1,radius-1);
        fovy(visibles,x,y,1,radius-1);
        fovx(visibles,x,y,-1,radius-1);
        fovxy(visibles,x,y,-1,-1,radius-2,radius-2);
        fovxy(visibles,x,y,1,-1,radius-2,radius-2);
        fovxy(visibles,x,y,1,1,radius-2,radius-2);
        fovxy(visibles,x,y,-1,1,radius-2,radius-2);
    }
    const int& operator()(const int x, const int y)const{return layers[1][x+y*width];}
    ~Map(){for(auto& layer : layers) delete[] layer;}
    ///Loads map from a file
    Map(const char *file);
    int width;
    int height;
    ///Traces a ray from position in a direction and returns the hit position
    Vector2 raycast(const Vector2 position, const Vector2 direction)const{return (layers[1][int(position.x)+int(position.y)*width]==-1)?raycast(position+direction,direction):position;}
};
