#include <eK.hpp>
#include <cmath>
using namespace std::chrono;

tObject *tObject::move(int tx, int ty){
  x0 = x;
  y0 = y;
  Ax = tx-x;
  Ay = ty-y;
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
  if(speed*At >= Axy)
    return this;
  x = x0+(Ax/Axy)*speed*At;
  y = y0+(Ay/Axy)*speed*At;
  return this;
}

tObject *tObject::draw(tTMX *map){
  sprite->draw(map->xtracecast(x),map->ytracecast(y),rot);
  return this;
}
