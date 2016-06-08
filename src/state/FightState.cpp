#include "FightState.h"
#include "../display/SimpleButton.h"
#include "MenuState.h"

spFightState FightState::instance;

FightState::FightState() {
	createGame();

	_pauseMenu = initActor(new Sprite,
		arg_resAnim = GameResource::ui.getResAnim("pause"),
		arg_anchor = Vector2(0.5f, 0.5f),
		arg_name = "Pause Menu",
		arg_visible = false,
		arg_attachTo = _view);
	_pauseMenu->setX(_view->getWidth() / 2);
	_pauseMenu->setY(_view->getHeight() / 2);

	this->_initPauseMenu();
}

void FightState::_show() {
	// load objects
	_fightContainer->init();

	// add events to menu
	_pauseMenu->addEventListener(TouchEvent::CLICK, CLOSURE(this, &FightState::onEvent));
	getStage()->addEventListener(KeyEvent::KEY_DOWN, CLOSURE(this, &FightState::onKeyEvent));
}

void FightState:: _initPauseMenu() {

	float buttonX = _pauseMenu->getWidth() / 2;
	float buttonY = _pauseMenu->getHeight() / 2 + 50;

	char* pauseBtns[] = { "RESUME [P]","EXIT TO MAIN MENU [M]" };
	char* pauseBtnsName[] = { "resume", "exit" };

	spSimpleButton button;
	for (int i = 0; i < 2; i++) {
		button = new SimpleButton();
		button->setName(pauseBtnsName[i]);
		button->setAnchor(Vector2(0.5f, 0.5f));
		button->setText(pauseBtns[i]);
		button->attachTo(_pauseMenu);
		button->setPosition(buttonX, buttonY);

		buttonY += 50;
	}
}

void FightState::onEvent(Event* event) {
	const std::string target = event->target->getName();

	// switch to menu
	if (target == "exit") {
		closeGame();
		changeState(MenuState::instance);
	} 
	else if (target == "resume") {
		_isPaused = !_isPaused;
		_pauseMenu->setVisible(false);
		_fightContainer->getClock()->resume();
	}
}

void FightState::onKeyEvent(Event* event) {
	KeyEvent* ke = safeCast<KeyEvent*>(event);

	if (ke->type = KeyEvent::KEY_DOWN) {
		if (SDL_SCANCODE_P == ke->data->keysym.scancode && _isPaused == true) {
			_isPaused = !_isPaused;
			_pauseMenu->setVisible(false);
			_fightContainer->getClock()->resume();
		}
		else if (SDL_SCANCODE_P == ke->data->keysym.scancode && _isPaused == false) {
			_fightContainer->getClock()->pause();
			_isPaused = !_isPaused;
			_pauseMenu->setVisible(true);
		}
		else if (SDL_SCANCODE_M == ke->data->keysym.scancode && _isPaused == true) {
			closeGame();
			changeState(MenuState::instance);
		}
	}
}

void FightState::createGame() {
	_fightContainer = new FightStage();
	_fightContainer->setClock(new Clock());
	_view->prependChild(_fightContainer);
}

void FightState::closeGame() {
	//reset game
	_fightContainer->detach();
	_pauseMenu->setVisible(false);
	_isPaused = false;

	// prepare new game
	createGame();

	//remove events
	getStage()->removeEventListener(KeyEvent::KEY_DOWN, CLOSURE(this, &FightState::onKeyEvent));
	_pauseMenu->addEventListener(TouchEvent::CLICK, CLOSURE(this, &FightState::onEvent));
}