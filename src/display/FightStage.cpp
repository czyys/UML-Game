#include "FightStage.h"
#include "../core/Config.h"
#include "../resource/GameResource.h"
#include "Pickup.h"
#include "../state/MenuState.h"


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

	_initBgClouds();

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

	spTextField textDetails = new TextField();
	textDetails->setTouchEnabled(false);
	const Font* systemFont = textDetails->getFont();

	// create aircrafts, get keys from config
	this->_af1 = new AircraftFighter();
	this->_af1->init(Vector2(0,0), 180, this);
	this->_af1->setKeys(Config::getInstance().getPlayerKeys(0));
	
	// update aircraft position
	this->_af1->setPosition(Vector2(this->getWidth() / 2 - this->_af1->getWidth() / 2, this->getHeight() - this->_af1->getHeight()));
	
	//GUI initialization
	_initGui();

	this->_af1->setKeys(Config::getInstance().getPlayerKeys(0));

	spTextField playerNameRed = createText("RED PLAYER", "red");
	playerNameRed->setText(Config::getInstance().getPlayerName(1));
	playerNameRed->attachTo(this);
	playerNameRed->setX(this->getWidth()-170);
	playerNameRed->setY(35);

	spTextField playerNameGreen = createText("GREEN PLAYER", "green");
	playerNameRed->setText(Config::getInstance().getPlayerName(2));
	playerNameGreen->attachTo(this);
	playerNameGreen->setX(this->getWidth() - 170);
	playerNameGreen->setY(this->getHeight() - 25);
}


void FightStage::_initGui() {
	this->_guiPLayerRed = new Sprite();
	this->_guiPLayerRed->setResAnim(GameResource::ui.getResAnim("fight-gui"));
	this->_guiPLayerRed->attachTo(this);

	this->_guiPLayerGreen = new Sprite();
	this->_guiPLayerGreen->setResAnim(GameResource::ui.getResAnim("fight-gui"));
	this->_guiPLayerGreen->attachTo(this);
	this->_guiPLayerGreen->setFlipped(false, true);

	this->_guiPLayerRed->setY(_bg->getHeight() - 64);
	this->_guiPLayerRed->setX(0);

	this->_guiPLayerGreen->setY(0);
	this->_guiPLayerGreen->setX(0);
	
}

spTextField FightStage::createText(const std::string& txt, const std::string& color){
	
	spTextField textDetails = new TextField();
	textDetails->setTouchEnabled(false);
	const Font* systemFont = textDetails->getFont();

	TextStyle st;
	st.font = textDetails->getFont();
	st.vAlign = TextStyle::VALIGN_BOTTOM;
	st.multiline = false;
	st.fontSize2Scale = 18;

	if (color == "red") {
		st.color = Color(211, 41, 41, 255);
	}
	else if(color == "green") {
		st.color = Color(112, 228, 88, 255);
	}
	else {
		st.color = Color(255, 255, 255, 255);
	}

	textDetails->setText(txt);
	textDetails->setStyle(st);
	return textDetails;
}

void FightStage::_initBgClouds() {
	this->_bgClouds = new Sprite();
	this->_bgClouds->setResAnim(GameResource::ui.getResAnim("fight-bg-clouds"));
	this->_bgClouds->attachTo(this);

	this->_bgClouds->setY(0);
	this->_bgClouds->setX(-1000);

	//animation duration
	int duration = 4 * 60 * 1000; // 1 minute
	_fightStageTween = this->_bgClouds->addTween(Actor::TweenPosition(_bgClouds->getPosition() + Vector2(+1524, 0)), duration, 0, true);

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