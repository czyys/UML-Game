#include "FightState.h"
#include "../display/SimpleButton.h"
#include "MenuState.h"

spFightState FightState::instance;

FightState::FightState() {
	_fightContainer = new FightStage();
	_fightContainer->attachTo(this->_view);
	_fightContainer->setClock(_clock = new Clock());

	_pauseMenu = initActor(new Sprite,
		arg_resAnim = GameResource::ui.getResAnim("pause"),
		arg_anchor = Vector2(0.5f, 0.5f),
		arg_attachTo = _view);
	_pauseMenu->setX(_view->getWidth() / 2);
	_pauseMenu->setY(_view->getHeight() / 2);

	this->_initPauseMenu();

	_pauseMenu->setName("Pause Menu");
	_pauseMenu->setVisible(false);

	// add events to menu
	_pauseMenu->addEventListener(TouchEvent::CLICK, CLOSURE(this, &FightState::onEvent));
	getStage()->addEventListener(KeyEvent::KEY_DOWN, CLOSURE(this, &FightState::onKeyEvent));
}

void FightState::_show() {
	_fightContainer->init();
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

		changeState(MenuState::instance);
		getStage()->removeEventListener(KeyEvent::KEY_DOWN, CLOSURE(this, &FightState::onKeyEvent));

		_pauseMenuTween = _pauseMenu->addTween(Actor::TweenY(_pauseMenu->getY() - 20), 400);
		_pauseMenuTween->setDoneCallback(CLOSURE(this, &FightState::onTweenDone));
	} 
	else if (target == "resume") {

		_isPaused = !_isPaused;
		_pauseMenu->setVisible(false);
		_clock->resume();
	}
}

void FightState::onKeyEvent(Event* event) {

	KeyEvent* ke = safeCast<KeyEvent*>(event);

	if (ke->type = KeyEvent::KEY_DOWN) {
		if (SDL_SCANCODE_P == ke->data->keysym.scancode && _isPaused == true) {
			_isPaused = !_isPaused;
			_pauseMenu->setVisible(false);
			_clock->resume();
		}
		else if (SDL_SCANCODE_P == ke->data->keysym.scancode && _isPaused == false) {
			_isPaused = !_isPaused;
			_pauseMenu->setVisible(true);
			_clock->pause();
		}
		else if (SDL_SCANCODE_M == ke->data->keysym.scancode && _isPaused == true) {
			changeState(MenuState::instance);
			getStage()->removeEventListener(KeyEvent::KEY_DOWN, CLOSURE(this, &FightState::onKeyEvent));
		}
	}
}

void FightState::onTweenDone(Event* event) {
	float posY = 0;
	spSprite state;

	// animation
	posY = state->getY() + 20;
	state->addTween(Actor::TweenAlpha(255), 200);
	state->addTween(Actor::TweenY(posY), 400);
}