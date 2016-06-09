#include "Rocket.h"
#include "../resource/GameResource.h"
#include "FightStage.h"
#include "Obstacle.h"
#include "AircraftFighter.h"

Rocket::Rocket(const Vector2& dir, std::string senderName): _dir(dir),_senderName(senderName){
}

void Rocket::_init(){
    //initialize rocket's sprite
    spSprite sp = new Sprite;
    sp->setResAnim(GameResource::ui.getResAnim("rocket"));
    sp->setAnchor(Vector2(0.5f, 0.5f));
    sp->setScale(0);
    sp->addTween(Sprite::TweenScale(1.0f), 500);

    _view->addChild(sp);
    _view->setRotation(atan2f(_dir.y, _dir.x));
}

void Rocket::_update(const UpdateState& us){
	//move rocket by it's direction each frame
	Vector2 pos = _view->getPosition();
	pos += _dir * (us.dt / 1000.0f) * 500.0f;
	_view->setPosition(pos);

	//find intersection with Enemies and explode them
	

	for (std::list<spUnit>::iterator i = _game->_units.begin(); i != _game->_units.end(); ++i) {
		spUnit unit = *i;
		//list of units has everything, but we need only Enemies
		spAircraftFighter player = dynamic_cast<AircraftFighter*>(unit.get());
		spObstacle obstacle = dynamic_cast<Obstacle*>(unit.get());
		/* cyrrently no obstacles*/
		if (obstacle)
		{


			Vector2 d = unit->getPosition() - pos;
			if (d.length() < 20)
			{
				//if rocket is too close to Enemy then try to explode it and explode rocket
				obstacle->hit(1);
				explode();
				return;
			}


		}
		else if (player)
		{
			Vector2 d = unit->getPosition() - pos;
			if (d.length() < 20)
			{
				if (player->getName() != _senderName)
				{
					player->hit(1);
					explode();
					return;
				}
			}
		}
		else continue;
		
	}
	
    //if rocked out of bounds then explode it
    RectF bounds(0, 0, getStage()->getWidth(), getStage()->getHeight());
    if (!bounds.pointIn(pos)){
        explode();
    }
}

void Rocket::explode(){
    //Rocket  commitet suicide
    //set this flag to true and it this rocket would be removed from units list in Game::doUpdate
    _dead = true;

    //create explode sprite
    spSprite anim = new Sprite;
    anim->attachTo(_game);
    anim->setBlendMode(blend_add);
    anim->setPosition(_view->getPosition());
    anim->setAnchor(Vector2(0.5f, 0.5f));

    //run tween with explosion animation
    spTween tween = anim->addTween(Sprite::TweenAnim(GameResource::ui.getResAnim("explosion")), 200);
    //auto detach sprite when tween is done
    tween->setDetachActor(true);

    //hide rocket and then detach it
    tween = _view->addTween(Actor::TweenAlpha(0), 500);
    tween->setDetachActor(true);
}