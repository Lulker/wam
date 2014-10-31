#include <eK.hpp>
#include <cmath>
using namespace std::chrono;

tObject::tObject(tSprite *sprite, float x, float y, float speed){
  ms = speed;
  cx = x;
  cy = y;
  s = sprite;
  move(cx,cy);
}

tObject *tObject::move(int tx, int ty){
  x0 = cx;
  y0 = cy;
  Ax = tx-cx;
  Ay = ty-cy;
  Axy = sqrt(Ax*Ax + Ay*Ay);
  move_timestamp = steady_clock::now();
  return this;
}

tObject *tObject::aim(){
  rot = atan2(Ay,Ax)*180/M_PI;
  return this;
}

tObject *tObject::update(){
  float At = (duration_cast<duration<float>>(steady_clock::now() - move_timestamp)).count();
  if(ms*At >= Axy)
    return this;
  cx = x0 + (Ax/Axy)*ms*At;
  cy = y0 + (Ay/Axy)*ms*At;
  return this;
}

tObject *tObject::draw(tTMX *map){
  s->draw(map->xtracecast(cx),map->ytracecast(cy),rot);
  return this;
}
