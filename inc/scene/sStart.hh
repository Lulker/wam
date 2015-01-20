#include "sMenu.hh"
struct sStart:Scene {Scene* operator()(){return new sMenu;}};
