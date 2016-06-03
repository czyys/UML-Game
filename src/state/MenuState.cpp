#include "MenuState.h"
#include "Sprite.h"
#include "initActor.h"
#include "../resource/GameResource.h"
#include "../display/SimpleButton.h"
#include "../core/Config.h"
#include "FightState.h"

using namespace std;

spMenuState MenuState::instance;

MenuState::MenuState(){

	//create main state background
	spSprite sky = new Sprite;
	sky->setResAnim(GameResource::ui.getResAnim("bg"));
	sky->attachTo(_view);

	//create logo
	spSprite logo = initActor(new Sprite,
		arg_resAnim = GameResource::ui.getResAnim("logotype"),
		arg_attachTo = _view);
	logo->setX(_view->getWidth() - logo->getWidth() - 20);
	logo->setY(_view->getHeight() - (_view->getHeight() - logo->getHeight()/4));

	//create menu block
	_mainMenu = initActor(new Sprite,
		arg_resAnim = GameResource::ui.getResAnim("menu-bg"),
		arg_anchor = Vector2(0.5f, 0.5f),
		arg_attachTo = _view);
	_mainMenu->setX(_view->getWidth() / 2);
	_mainMenu->setY((_view->getHeight() / 2) + 80);

	//create settings block
	_playerSettings = initActor(new Sprite,
		arg_resAnim = GameResource::ui.getResAnim("set_bg"),
		arg_anchor = Vector2(0.5f, 0.5f),
		arg_name = "settings",
		arg_attachTo = _view);
	_playerSettings->setX(_view->getWidth() / 2);
	_playerSettings->setY((_view->getHeight() / 2) + 60);
	
	this->_initEngineEffects();
	this->_initFireBottomEffects();
	this->_initSmokeBottomEffects();
	this->_initSparksTopEffects();
	this->_initSettings(
		Config::getInstance().getPlayerName(0), 
		Config::getInstance().getPlayerName(1),
		Config::getInstance().getPlayerKeys(0),
		Config::getInstance().getPlayerKeys(1)
	);

	this->_initMenu();
	
	_mainMenu->setName("Main Menu");

	// add events to menu
	_mainMenu->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MenuState::onEvent));
}

void MenuState::_initMenu() {
	spActor menuClip = new Actor();
	menuClip->setSize(_mainMenu->getWidth(), _mainMenu->getHeight());
	menuClip->attachTo(_mainMenu);
	menuClip->setName("menuClip");

	float buttonX        = menuClip->getWidth() / 2;
	float buttonY        = 74;
	char* menuBtns[]     = {"PLAY", "SETTINGS", "AUTHORS", "WE ON GITHUB", "EXIT THE GAME"};
	char* menuBtnsName[] = {"play", "settings", "authors", "github", "exit"};

	spSimpleButton button;

	for (int i = 0; i < 5; i++) {
		button = new SimpleButton();
		button->setName(menuBtnsName[i]);
		button->setAnchor(Vector2(0.5f, 0.5f));
		button->setText(menuBtns[i]);
		button->attachTo(menuClip);
		button->setPosition(buttonX, buttonY);

		buttonY += button->getHeight() + 13;
	}
}

/**
	Important note:
	Input fields should be added in correct ordering(according to key ordering in config array) to parent container,
	because we loop over parent node later. 

	@see: MenuState::_backSettingsToDef()
*/
void MenuState::_initSettings(const std::string& playerName1, const std::string &playerName2, const std::vector<int> &playerKey1, const std::vector<int> &playerKey2) {
	_input = new InputText();
	_input->addEventListener(Event::COMPLETE, CLOSURE(this, &MenuState::onComplete));

	// copy keys from default(config)
	_playerKeys1 = playerKey1;
	_playerKeys2 = playerKey2;

	spInputField pName1     = new InputField(playerName1, true);
	spInputField pKeyUp1    = new InputField(playerKey1[0], false);
	spInputField pKeyDown1  = new InputField(playerKey1[2], false);
	spInputField pKeyLeft1  = new InputField(playerKey1[3], false);
	spInputField pKeyRight1 = new InputField(playerKey1[1], false);
	spInputField pKeyShot1  = new InputField(playerKey1[4], true);

	spInputField pName2     = new InputField(playerName2, true);
	spInputField pKeyUp2    = new InputField(playerKey2[0], false);
	spInputField pKeyDown2  = new InputField(playerKey2[2], false);
	spInputField pKeyLeft2  = new InputField(playerKey2[3], false);
	spInputField pKeyRight2 = new InputField(playerKey2[1], false);
	spInputField pKeyShot2  = new InputField(playerKey2[4], true);

	//action button
	spSimpleButton saveBtn   = new SimpleButton("small_btn");
	spSimpleButton cancelBtn = new SimpleButton("cancel_btn");
	
	// left column = player 1
	pName1->setName("p1");
	pName1->setPosition(39, 60);
	pName1->addLabel("Player 1:");
	pName1->attachTo(_playerSettings);
	
	pKeyUp1->setName("0-0");
	pKeyUp1->setPosition(39, 119);
	pKeyUp1->addLabel("Key Up:");
	pKeyUp1->setMaxKeyLength(1);
	pKeyUp1->attachTo(_playerSettings);

	pKeyRight1->setName("0-1");
	pKeyRight1->setPosition(142, 178);
	pKeyRight1->addLabel("Key Right:");
	pKeyRight1->setMaxKeyLength(1);
	pKeyRight1->attachTo(_playerSettings);

	pKeyDown1->setName("0-2");
	pKeyDown1->setPosition(142, 119);
	pKeyDown1->addLabel("Key Down:");
	pKeyDown1->setMaxKeyLength(1);
	pKeyDown1->attachTo(_playerSettings);

	pKeyLeft1->setName("0-3");
	pKeyLeft1->setPosition(39, 178);
	pKeyLeft1->addLabel("Key Left:");
	pKeyLeft1->setMaxKeyLength(1);
	pKeyLeft1->attachTo(_playerSettings);

	pKeyShot1->setName("0-4");
	pKeyShot1->setPosition(39, 237);
	pKeyShot1->addLabel("Key Shot:");
	pKeyShot1->setMaxKeyLength(1);
	pKeyShot1->attachTo(_playerSettings);

	// right column = player 2
	pName2->setName("p2");
	pName2->setPosition(302, 60);
	pName2->addLabel("Player 2:");
	pName2->attachTo(_playerSettings);

	pKeyUp2->setName("1-0");
	pKeyUp2->setPosition(302, 119);
	pKeyUp2->addLabel("Key Up:");
	pKeyUp2->setMaxKeyLength(1);
	pKeyUp2->attachTo(_playerSettings);

	pKeyRight2->setName("1-1");
	pKeyRight2->setPosition(405, 178);
	pKeyRight2->addLabel("Key Right:");
	pKeyRight2->setMaxKeyLength(1);
	pKeyRight2->attachTo(_playerSettings);

	pKeyDown2->setName("1-2");
	pKeyDown2->setPosition(405, 119);
	pKeyDown2->addLabel("Key Down:");
	pKeyDown2->setMaxKeyLength(1);
	pKeyDown2->attachTo(_playerSettings);

	pKeyLeft2->setName("1-3");
	pKeyLeft2->setPosition(302, 178);
	pKeyLeft2->addLabel("Key Left:");
	pKeyLeft2->setMaxKeyLength(1);
	pKeyLeft2->attachTo(_playerSettings);

	pKeyShot2->setName("1-4");
	pKeyShot2->setPosition(302, 237);
	pKeyShot2->addLabel("Key Shot:");
	pKeyShot2->attachTo(_playerSettings);
	
	// bottom row = actions
	saveBtn->setText("SAVE");
	saveBtn->setName("saveBTN");
	saveBtn->setPosition(164, 310);
	saveBtn->attachTo(_playerSettings);
	
	cancelBtn->setText("CANCEL");
	cancelBtn->changeColor(Color::Red);
	cancelBtn->setName("cancelBTN");
	cancelBtn->setPosition(282, 310);
	cancelBtn->attachTo(_playerSettings);
	
	// add events
	_playerSettings->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MenuState::onClickTF));
	
	// hide menu
	_playerSettings->setAlpha(0);
};

void MenuState::_backSettingsToDef() {
	unsigned int i = 0;
	_playerKeys1 = Config::getInstance().getPlayerKeys(0);
	_playerKeys2 = Config::getInstance().getPlayerKeys(1);

	// first player
	_currentTF = safeSpCast<InputField>(_playerSettings->getFirstChild());
	_currentTF->getTextField()->setText(Config::getInstance().getPlayerName(0));

	for (i = 0; i < _playerKeys1.size(); i++) {
		_currentTF = safeSpCast<InputField>(_currentTF->getNextSibling());
		_currentTF->setContentText(_playerKeys1[i]);
	}

	// second player
	_currentTF = safeSpCast<InputField>(_currentTF->getNextSibling());
	_currentTF->getTextField()->setText(Config::getInstance().getPlayerName(1));

	for (i = 0; i < _playerKeys2.size(); i++) {
		_currentTF = safeSpCast<InputField>(_currentTF->getNextSibling());
		_currentTF->setContentText(_playerKeys2[i]);
	}
	
	// clear current text field
	_currentTF = 0;
}

void MenuState::_saveSettingsToConfig() {
	_currentTF = _playerSettings->getChildT<InputField>("p1");
	std::string pName1 = _currentTF->getTextField()->getText();

	_currentTF = _playerSettings->getChildT<InputField>("p2");
	std::string pName2 = _currentTF->getTextField()->getText();

	Config::getInstance().setPlayerName(0, pName1);
	Config::getInstance().setPlayerName(1, pName2);
	Config::getInstance().setPlayerKeys(0, _playerKeys1);
	Config::getInstance().setPlayerKeys(1, _playerKeys2);

	Config::getInstance().saveConfig();
};

void MenuState::_initEngineEffects() {
	_enginesAnimation = new Sprite();
	_enginesAnimation->attachTo(_view);
	_enginesAnimation->setAnchor(0.5f, 0.5f);
	_enginesAnimation->setResAnim(GameResource::ui.getResAnim("engines-fire"));

	//engines animation initial position
	_enginesAnimation->setX(_view->getWidth() / 2 - 160);
	_enginesAnimation->setY(_view->getHeight() / 2 - 213);

	_mainStateEffectsTween = _enginesAnimation->addTween(TweenAnim(GameResource::ui.getResAnim("engines-fire")), 700, 0);
	log::messageln("show main state Engine effects");
}

void MenuState::_initFireBottomEffects() {
	_fireBottomAnimation = new Sprite();
	_fireBottomAnimation->attachTo(_view);
	_fireBottomAnimation->setAnchor(0.5f, 0.5f);
	_fireBottomAnimation->setResAnim(GameResource::ui.getResAnim("fire_bottom_anim"));
	_fireBottomAnimation->setTouchEnabled(false);

	//fire animation initial position
	_fireBottomAnimation->setX(_view->getWidth() - _fireBottomAnimation->getWidth() / 3);
	_fireBottomAnimation->setY(_view->getHeight() / 2 + _fireBottomAnimation->getHeight() / 3 + 50);

	_mainStateEffectsTween = _fireBottomAnimation->addTween(Actor::TweenPosition(_fireBottomAnimation->getPosition() + Vector2(+350, 0)), 40000, 0, true);
	log::messageln("show main state Fire bottom effects");
}

void MenuState::_initSmokeBottomEffects() {
	_smokeLeftBottomAnimation = new Sprite();
	_smokeLeftBottomAnimation->attachTo(_view);
	_smokeLeftBottomAnimation->setAnchor(0.5f, 0.5f);
	_smokeLeftBottomAnimation->setResAnim(GameResource::ui.getResAnim("left_bottom_smoke_anim"));
	_smokeLeftBottomAnimation->setTouchEnabled(false);

	//smoke animation initial position
	_smokeLeftBottomAnimation->setX(_view->getWidth() - _view->getWidth() + _smokeLeftBottomAnimation->getWidth()-180);
	_smokeLeftBottomAnimation->setY(_view->getHeight() / 2 + 115);
	_smokeLeftBottomAnimation->setAlpha(10);

	_mainStateEffectsTween = _smokeLeftBottomAnimation->addTween(Actor::TweenAlpha(200), 4000, 0, true);
	log::messageln("show main state Smoke bottom effects");
}

void MenuState::_initSparksTopEffects() {
	_sparksTopRightAnimation = new Sprite();
	_sparksTopRightAnimation->attachTo(_view);
	_sparksTopRightAnimation->setAnchor(0.5f, 0.5f);
	_sparksTopRightAnimation->setResAnim(GameResource::ui.getResAnim("sparks_top_anim"));
	_sparksTopRightAnimation->setAlpha(200);
	_sparksTopRightAnimation->setTouchEnabled(false);

	//sparks animation initial position
	_sparksTopRightAnimation->setX(_view->getWidth());
	_sparksTopRightAnimation->setY(_view->getHeight() - (_view->getHeight() /4)*3);

	_mainStateEffectsTween = _sparksTopRightAnimation->addTween(Actor::TweenPosition(_sparksTopRightAnimation->getPosition() + Vector2(-350, 0)), 40000, 0, true);
	log::messageln("show main state Smoke bottom effects");
}

void MenuState::onEvent(Event* ev) {
	const std::string target = ev->target->getName();

	// exit app
	if (target == "exit") {
		core::requestQuit();
	}
	else if (target == "play") {
		log::messageln("mode changed");
		
		//clicked to play button change scene
		changeState(FightState::instance);
	}
	else if (target == "settings") {
		_nextState = MenuState::MENU_SETTINGS;
		
		_mainMenu->addTween(Actor::TweenAlpha(0), 200);
		_mainMenuTween = _mainMenu->addTween(Actor::TweenY(_mainMenu->getY() - 20), 400);
		
		_mainMenuTween->setDoneCallback(CLOSURE(this, &MenuState::onTweenDone));
	}
	else if (target == "auth-normal") {
		
	}
}

void MenuState::onClickTF(Event* ev) {
	const std::string target = ev->target->getName();

	// unselect current text field if other element has been touched
	if (_currentTF != 0) {
		_currentTF->updateTextField();
		_currentTF->focus(false);
		_currentTF = 0;
		InputText::stopAnyInput();
	}

	// main panel has been touched (probably for unselect current text field) 
	if (target == "settings") return;

	// save btn clicked
	if (target == "saveBTN") {
		_nextState = MenuState::MAIN_MENU;
		_task = MenuState::TASK_SAVE;

		_playerSettings->addTween(Actor::TweenAlpha(0), 200);
		_mainMenuTween = _playerSettings->addTween(Actor::TweenY(_playerSettings->getY() - 20), 400);
		_mainMenuTween->setDoneCallback(CLOSURE(this, &MenuState::onTweenDone));

		return;
	}

	// cancel btn clicked
	if (target == "cancelBTN") {
		_nextState = MenuState::MAIN_MENU;
		_task      = MenuState::TASK_CANCEL;

		_playerSettings->addTween(Actor::TweenAlpha(0), 200);
		_mainMenuTween = _playerSettings->addTween(Actor::TweenY(_playerSettings->getY() - 20), 400);
		_mainMenuTween->setDoneCallback(CLOSURE(this, &MenuState::onTweenDone));

		return;
	}

	// text field clicked
	_currentTF = safeSpCast<InputField>(ev->target);
	_currentTF->focus(true);
	_input->start(_currentTF->getTextField());

	if (_currentTF->getMaxKeyLength() == 1) {
		getStage()->addEventListener(KeyEvent::KEY_DOWN, CLOSURE(this, &MenuState::onKeyEvent));
	}
};

void MenuState::onKeyEvent(Event* ev) {
	KeyEvent* ke = safeCast<KeyEvent*>(ev);

	if (ke->type = KeyEvent::KEY_DOWN) {
		getStage()->removeEventListener(KeyEvent::KEY_DOWN, CLOSURE(this, &MenuState::onKeyEvent));
		const char* keyName = SDL_GetScancodeName(ke->data->keysym.scancode);
		_currentTF->getTextField()->setText(keyName);
		_currentTF->focus(false);
		InputText::stopAnyInput();

		// save in keys array
		std::string tfName = _currentTF->getName();
		
		short tfPlayer = std::atoi(&tfName.at(0));
		short tfID = std::atoi(&tfName.at(2));
		
		if (tfPlayer == 0) {
			_playerKeys1[tfID] = ke->data->keysym.scancode;
		}
		else {
			_playerKeys2[tfID] = ke->data->keysym.scancode;
		}

		// reset current text field
		_currentTF = 0;
	}
}

void MenuState::onComplete(Event* ev) {
	if (_currentTF) {
		_currentTF->focus(false);
		_currentTF->updateTextField();
	}
	_currentTF = 0;
	InputText::stopAnyInput();
};

void MenuState::onTweenDone(Event* ev) {
	log::message("tween done");
	float posY = 0;

	switch (_nextState) {
	case MenuState::MENU_SETTINGS:
		posY = _playerSettings->getY() + 20;
		_playerSettings->addTween(Actor::TweenAlpha(255), 200);
		_playerSettings->addTween(Actor::TweenY(posY), 400);
		
		break;
	case MenuState::MAIN_MENU:
		posY = _mainMenu->getY() + 20;
		_mainMenu->addTween(Actor::TweenAlpha(255), 200);
		_mainMenuTween = _mainMenu->addTween(Actor::TweenY(posY), 400);
		break;
	}

	switch (_task) {
	case MenuState::TASK_SAVE:
		_saveSettingsToConfig();
		break;
	case MenuState::TASK_CANCEL:
		// back to default settings(discard changes)
		_backSettingsToDef();
		break;
	default:
		break;
	}
}