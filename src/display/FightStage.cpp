#include "FightStage.h"
#include "../core/Config.h"
#include "../resource/GameResource.h"
#include "Pickup.h"

FightStage::FightStage() {

}

FightStage::~FightStage() {
	//getStage()->removeEventListener(KeyEvent::KEY_DOWN);
}

void FightStage::init() {
	this->setSize(getStage()->getSize());

	// create background
	this->_bg = new Sprite();
	this->_bg->setResAnim(GameResource::ui.getResAnim("sky"));
	this->_bg->attachTo(this);

	spPickup pickup_pup0 = new Pickup("pup", 0, 5, 20);
	pickup_pup0->init(Vector2(scalar::randFloat(0, getWidth()), scalar::randFloat(0, getHeight())), 0, this);
	spPickup pickup_pup1 = new Pickup("pup", 1, 5, 20);
	pickup_pup1->init(Vector2(scalar::randFloat(0, getWidth()), scalar::randFloat(0, getHeight())), 0, this);
	spPickup pickup_pup2 = new Pickup("pup", 2, -1, 76);
	pickup_pup2->init(Vector2(scalar::randFloat(0, getWidth()), scalar::randFloat(0, getHeight())), 0, this);
	spPickup pickup_pup3 = new Pickup("pup", 3, -1, 76);
	pickup_pup3->init(Vector2(scalar::randFloat(0, getWidth()), scalar::randFloat(0, getHeight())), 0, this);
	spPickup pickup_wpn0 = new Pickup("wpn", 0, 5, 20);
	pickup_wpn0->init(Vector2(scalar::randFloat(0, getWidth()), scalar::randFloat(0, getHeight())), 0, this);
	spPickup pickup_wpn1 = new Pickup("wpn", 1, 5, 20);
	pickup_wpn1->init(Vector2(scalar::randFloat(0, getWidth()), scalar::randFloat(0, getHeight())), 0, this);

	// create aircrafts, get keys from config
	this->_af1 = new AircraftFighter();
	this->_af1->init(Vector2(0,0), 180, this);
	this->_af1->setKeys(Config::getInstance().getPlayerKeys(0));
	
	// update aircraft position
	this->_af1->setPosition(Vector2(this->getWidth() / 2 - this->_af1->getWidth() / 2, this->getHeight() - this->_af1->getHeight()));
	
	// add listeners
	//getStage()->addEventListener(KeyEvent::KEY_DOWN, CLOSURE(this, &FightStage::onEvent));
}

void FightStage::doUpdate(const UpdateState& us) {
	// update display objects
	for (std::list<spUnit>::iterator i = _units.begin(); i != _units.end(); ){
		spUnit child = *i;
		child->update(us);

		if (child->isDead()){
			//it is dead. Time to remove it from list
			i = _units.erase(i);
		} else {
			++i;
		}
	}
}

void FightStage::onEvent(Event* ev) {
	KeyEvent* ke = safeCast<KeyEvent*>(ev);
	
	if (ke->type == KeyEvent::KEY_DOWN) {
		switch (ke->data->keysym.scancode) {
		case SDL_SCANCODE_ESCAPE:
			log::messageln("escape down");
			break;
		default:
			log::messageln("other key pressed");
			break;
		}
	}
}

void FightStage::_showMenu() {

}