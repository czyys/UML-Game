#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

class FightStage;

DECLARE_SMART(Unit, spUnit);
class Unit: public Object{
protected:
	spActor     _view;
	FightStage* _game;
	bool        _dead;

	virtual void _init() {}
	virtual void _update(const UpdateState& us) {}

public:
    Unit();

    void init(const Vector2& pos, float rotation, FightStage* game);

    const Vector2& getPosition() const;
	void setPosition(Vector2 newPosition);
    void update(const UpdateState& us);
    bool isDead() const {return _dead;}
	float getHeight();
	float getWidth();
	spActor getView();
};