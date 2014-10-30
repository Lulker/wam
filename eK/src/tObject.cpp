#include <eK.hpp>
#include <cmath>
using namespace std::chrono;

tObject::tObject(tSprite *sprite, float x, float y, float speed){
  ms = speed;
  cx = x;
  cy = y;
  s = sprite;
}

void tObject::move(int tx, int ty){
  x0 = cx;
  y0 = cy;
  Ax = tx-cx;
  Ay = ty-cy;
  Axy = sqrt(Ax*Ax + Ay*Ay);
  move_timestamp = steady_clock::now();
}

tObject *tObject::update(){
  float At = (duration_cast<duration<float>>(steady_clock::now() - move_timestamp)).count();
  if(ms*At > Axy)
    return this;
  cx = x0 + (Ax/Axy)*ms*At;
  cy = y0 + (Ay/Axy)*ms*At;
  return this;
}

void tObject::draw(tTMX *map){
  s->draw(map->xtracecast(cx),map->ytracecast(cy));
}
