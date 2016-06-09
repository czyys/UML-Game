#include "ResultState.h"
#include "Sprite.h"
#include "initActor.h"
#include "MenuState.h"
#include "../resource/GameResource.h"
#include "../display/SimpleButton.h"
#include "FightState.h"
#include "../core/Config.h"
#ifdef _WIN32
#pragma comment(lib, "shell32.lib")
#include <windows.h>
#endif

using namespace std;
spResultState ResultState::instance;

ResultState::ResultState() {
	spSprite resultbg = new Sprite;
	resultbg->setResAnim(GameResource::ui.getResAnim("result"));
	resultbg->attachTo(_view);

	_resultMode = initActor(new Sprite,
		arg_resAnim = GameResource::ui.getResAnim("result-menu"),
		arg_anchor = Vector2(0.5f, 0.5f),
		arg_attachTo = _view);
	_resultMode->setX(_view->getWidth() / 2);
	_resultMode->setY((_view->getHeight() / 2) + 80);
	_resultMode->setTouchEnabled(false);

	//create logo
	spSprite gameover = initActor(new Sprite,
		arg_resAnim = GameResource::ui.getResAnim("game_over"),
		arg_anchor = Vector2(0.5f, 0.5f),
		arg_attachTo = _view);
	gameover->setX(_view->getWidth()/2);
	gameover->setY(_view->getHeight()/4 - 20);

	this->_initResult();
	_resultMode->addEventListener(TouchEvent::CLICK, CLOSURE(this, &ResultState::onEvent));
}

void ResultState::_initResult() {
	float buttonX = _resultMode->getWidth() / 2;
	float buttonY = 74;
	char* menuBtns[] = { "MENU", "RESTART", "EXIT" };
	char* menuBtnsName[] = { "menu", "restart", "exit" };

	spSimpleButton button;

	for (int i = 0; i < 3; i++) {
		button = new SimpleButton();
		button->setName(menuBtnsName[i]);
		button->setAnchor(Vector2(0.5f, 0.5f));
		button->setText(menuBtns[i]);
		button->attachTo(_resultMode);
		button->setPosition(buttonX, buttonY);
		buttonY += button->getHeight() + 13;
	}
}

void ResultState::onEvent(Event* ev) {
	const std::string target = ev->target->getName();

	if (target == "menu") {
		log::messageln("mode changed restart");
		changeState(MenuState::instance);
		return;
	}
	else if (target == "restart") {
		log::messageln("mode changed exit");
		changeState(FightState::instance);
		return;
	}
	else if (target == "exit") {
		core::requestQuit();
	}
}
