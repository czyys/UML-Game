#include "Pause.h"
#include "../resource/GameResource.h"
#include "AircraftFighter.h"
#include "FightStage.h"
#include "Unit.h"

Pause::Pause() {
}


Pause::~Pause() {
}


void Pause::_init() {
	//you could hit obstacle 3 times
	spSprite sprite = new Sprite;
	sprite->setResAnim(GameResource::ui.getResAnim("pause"));
	sprite->attachTo(_view);
	sprite->setAnchor(Point(0, 0));
}

void Pause::_update(const UpdateState& us) {

}