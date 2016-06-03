#include "FightState.h"

spFightState FightState::instance;

FightState::FightState() {
	_fightContainer = new FightStage();
	_fightContainer->attachTo(this->_view);
	_fightContainer->setClock(new Clock());

}

void FightState::_show() {
	_fightContainer->init();
}

void FightState::onEvent(Event* event) {
	
}