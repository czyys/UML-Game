#pragma once
#include "Unit.h"

using namespace oxygine;

DECLARE_SMART(Pause, spPause);
class Pause : public Unit {
protected:
	bool visible;

	void _init();
	void _update(const UpdateState& us);
	void _die();
	std::string  _type; //wpn/pup
	int _id; //with one
	Vector2 _pos; //where

public:
	Pause();
	~Pause();
};