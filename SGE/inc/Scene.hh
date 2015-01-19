#pragma once
#include "Meta.hh"
#include "uSDL.hh"
#include <functional>
class Scene : public BackCollector {
	public:
		/**
		* Hash map that contains functions for the different events
		* every event is identified by an int (corresponds to SDL event)
		* and contains a void function that gets event as parameter
		**/
		std::unordered_map<int,std::function<void(const eK_Event&)>> on;
		///Function executed when scene starts
		virtual void init(){};
		///Function executed every frame while scene lasts
		virtual void loop(const double &deltatime){};
		///Function executed when scene ends
		virtual void quit(){delete this;};
};
