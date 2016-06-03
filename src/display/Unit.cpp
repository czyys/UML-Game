#include "Unit.h"
#include "FightStage.h"

Unit::Unit(): _game(0), _dead(false){
	
}

void Unit::init(const Vector2& pos, float rotation, FightStage* game){
    //initialize base
    _game = game;

	_view = new Actor();
	_view->attachTo(game);
    _view->setPosition(pos);
	_view->setRotationDegrees(rotation);

    //adds to global units list
    _game->_units.push_back(this);
	
    //should be overloaded in inherited classes
    _init();
}

const Vector2& Unit::getPosition() const{
    return _view->getPosition();
}

void Unit::setPosition(Vector2 newPosition) {
	this->_view->setPosition(newPosition);
}

void Unit::update(const UpdateState& us)
{
    //should be overloaded in inherited classes
    _update(us);
}

float Unit::getHeight() {
	return this->_view->getHeight();
}

float Unit::getWidth() {
	return this->_view->getWidth();
}

spActor Unit::getView() {
	return this->_view;
}