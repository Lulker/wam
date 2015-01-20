#pragma once
#include "Meta.hh"
#include "uSDL.hh"
#include <functional>
struct Scene : public BackCollector {
	/**
	* Hash map that contains functions for the different events
	* every event is identified by an int (corresponds to SDL event)
	* and contains a void function that gets event as parameter
	**/
	std::unordered_map<int,std::function<void(const eK_Event&)>> on;
	///Function executed every frame while scene lasts
	virtual Scene* operator()()=0;
};
