#pragma once
#include "oxygine_include.h"
#include "Unit.h"

using namespace oxygine;

DECLARE_SMART(AircraftFighter, spAircraftFighter);

class AircraftFighter : public Unit{
protected:
	const char*      _color;
	const char*      _name;
	float            _speed;
	float            _speedMultiplier =1.0f;
	float            _speedPickUpMultiplier[2] = { 0.0f, 0.0f };
	timeMS           _lastPickUp[4] = { 0,0,0,0 };
	timeMS		     _currentTime;
	bool             _isFrozen;
	int              _hp;
	RectF            _bounds;
	timeMS           _lastBulletSpawn =0;
	spSprite         _ship;
	std::vector<int> _keyMap;

	void _init();
	void _update(const UpdateState& us);
	void _setDefaultKeys();

public:
	AircraftFighter();
	AircraftFighter(const char* name, const char* color);
	bool changeSpeed(bool accelerate);
	void setKeys(const std::vector<int> &keyMap);
	int hit(int damage);
	void pickupPup(int id);
	void pickupWpn(int id);
	void die();

	//Rocet need to know what to hit
	std::string getAircraftName()
	{
		return _name;
	}
	
};