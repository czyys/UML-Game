#pragma once
#include "oxygine-framework.h"
#include "State.h"
#include "../display/FightStage.h"

using namespace oxygine;

DECLARE_SMART(FightState, spFightState);

class FightState : public State{
private:
	bool		_isPaused = false;

	spFightStage _fightContainer;
	spSprite     _pauseMenu;

	void _show();
	void _initPauseMenu();
	void onEvent(Event* event);
	void onKeyEvent(Event* event);

public:
	static spFightState instance;
	FightState();
	void createGame();
	void closeGame();
};