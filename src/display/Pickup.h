#pragma once
#include "Unit.h"

using namespace oxygine;

DECLARE_SMART(Pickup, spPickup);
class Pickup : public Unit{
protected:
	void _init();
	void _update(const UpdateState& us);
	void _die();
	timeMS       _lastPickUp;
	std::string  _type; //wpn/pup
	int _id; //with one
	double _diameter; // from how far
	int _quantity;
	Vector2 _pos; //where
	bool _rotate;

public:
	Pickup(std::string type,  int id, int quantity, double diameter, bool rotate);
	~Pickup();
};

