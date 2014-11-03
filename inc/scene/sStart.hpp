#pragma once
#include <scene/sGame.hpp>

class sStart : public tScene
{
	public:
	void init(){ek->scene = new sGame;};
};
