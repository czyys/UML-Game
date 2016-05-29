#include "AircraftFighter.h"
#include "Rocket.h"
#include "../resource/GameResource.h"
#include <math.h>

AircraftFighter::AircraftFighter() : _lastBulletSpawn(0), _isFrozen(false) {
	this->_color = "red";
	this->_name = "Red Aircraft";
}

AircraftFighter::AircraftFighter(const char* name, const char* color) : _lastBulletSpawn(0), _isFrozen(false) {
	this->_color = color;
	this->_name = name;
}

void AircraftFighter::_init() {
	// set color to current aircraft
	std::string shipObj = "ship-";

	// set starting life points
	this->_hp = 5;

	// set initial speed 
	this->_speed = 10.0f;

	// create ship
	this->_ship = new Sprite();
	this->_ship->setResAnim(GameResource::ui.getResAnim(shipObj.append(this->_color)));
	this->_ship->setAnchor(Vector2(0.5f, 0.5f));
	this->_ship->attachTo(this->_view);

	this->_view->setWidth(this->_ship->getWidth());
	this->_view->setHeight(this->_ship->getHeight());

	// generate bounds
	this->_bounds = RectF(0, 0, getStage()->getWidth(), getStage()->getHeight());

	// load keys map
	this->_setDefaultKeys();
}

void AircraftFighter::_setDefaultKeys() {
	this->_keyMap[0] = SDL_SCANCODE_UP;
	this->_keyMap[1] = SDL_SCANCODE_RIGHT;
	this->_keyMap[2] = SDL_SCANCODE_DOWN;
	this->_keyMap[3] = SDL_SCANCODE_LEFT;
	this->_keyMap[4] = SDL_SCANCODE_SPACE;
}

void AircraftFighter::_update(const UpdateState& us) {
	Vector2 dir;
	Vector2 pos = this->getPosition();

	float _speedMultiplierPup = 0.0f;
	//get Pup multiplier
	for (int i = 0; i < 4; i++)
	{
		_speedMultiplierPup += _speedPickUpMultiplier[i];
	}

	_currentTime = us.time;
	float currentSpeed = ((this->_speed + _speedMultiplierPup)* this->_speedMultiplier )*(us.dt / 1000.0f);
	float angle = this->_view->getRotation();

	const Uint8* keyDown = SDL_GetKeyboardState(0);
	
	

	// set new position
	dir.set(-currentSpeed * 10 * sin(angle), currentSpeed * 10 * cos(angle));
	pos += dir;
	//log::messageln("S:%f SM:%f CS:%f PS:%f", _speed, _speedMultiplier, currentSpeed, _speedMultiplierPup);
	// Forward
	//if (keyDown[_keyMap[0]]) this->changeSpeed(true);
	//else this->changeSpeed(false);
	//if (keyDown[_keyMap[0]]) log::messageln("key up pressed");
	if (keyDown[_keyMap[2]]) this->_speedMultiplier = 0.5f;
	else if (keyDown[_keyMap[0]]) this->_speedMultiplier = 2.5f;
	else this->_speedMultiplier = 1.0f;

	// Right
	if (keyDown[_keyMap[1]]) angle += currentSpeed;

	// Backward
	//if (keyDown[_keyMap[2]]) log::messageln("key down pressed");
	//if (keyDown[_keyMap[2]]) this->_speedMultiplier = 0.5f;
	//else this->_speedMultiplier = 1.0f;
	// Left
	if (keyDown[_keyMap[3]]) angle -= currentSpeed;

	// Shot
	if (keyDown[_keyMap[4]]) {
		if (_lastBulletSpawn + 300 < us.time) {
			_lastBulletSpawn = us.time;

			dir.normalize();

			//create rocket
			spRocket rocket = new Rocket(dir, this->_name);
			rocket->init(_view->getPosition(), 0, _game);
		}
	}


	if (!_bounds.pointIn(pos)) {
		log::messageln("aircraft out of bounds");
		angle += (180 * M_PI) / 180;
	}

	this->_view->setPosition(pos);
	this->_view->setRotation(angle);

	//turn off pup 2,3

	if (_lastPickUp[2] + 400 < us.time) {
		_speedPickUpMultiplier[0] = 0.0f;

	if (_lastPickUp[3] + 400 < us.time) {
		_speedPickUpMultiplier[1] = 0.0f;

		}
	}
}

		/**
		* Change speed aircraft. If argument (accelerate) is equal true plane speed up, otherwise the plane speed down
		*
		* @param accelerate this specify speed the aircraft
		* @return If aircraft is not frozen (collision in cloud) return false, if speed is changed successfully return true
		*/
		bool AircraftFighter::changeSpeed(bool accelerate) {
			if (this->_isFrozen) {
				this->_speed = 2.0f;
				return false;
			}

			if (!accelerate) {
				this->_speedMultiplier = 2.5f;
				return true;
			}

			this->_speedMultiplier = 1.0f;
			return true;
		}

		void AircraftFighter::setKeys(int keyMaps[]) {
			*this->_keyMap = *keyMaps;
		}

		int AircraftFighter::hit(int damage) {
			return 0;
		}

		void AircraftFighter::pickupPup(int id) {

			switch (id) {
			case 2: //Spowolniajaca chmurka
			{
				_lastPickUp[2] = _currentTime;
				_speedPickUpMultiplier[0] = -5;
				break;
			}
			case 3: //Przyspieszajaca chmurka
			{
				_lastPickUp[3] = _currentTime;
				_speedPickUpMultiplier[1] =5;
				break;
			}

			}
		}

		void AircraftFighter::pickupWpn(int id) {
		}



		void AircraftFighter::die() {
		}