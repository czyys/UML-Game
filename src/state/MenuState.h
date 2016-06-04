#include "State.h"
#include "../display/InputField.h"
#include "../resource/GameResource.h"

DECLARE_SMART(MenuState, spMenuState);

class MenuState : public State{
private:
	spSprite     _mainMenu;
	spSprite     _playerSettings;
	spSprite     _menuAuthors;

	//animation special effects
	spSprite     _enginesAnimation;
	spSprite     _fireBottomAnimation;
	spSprite     _smokeLeftBottomAnimation;
	spSprite     _sparksTopRightAnimation;

	spTween      _mainMenuTween;
	spTween      _mainStateEffectsTween;
	spInputField _currentTF;
	spInputText  _input;

	short _nextState;
	short _task;

	std::vector<int> _playerKeys1;
	std::vector<int> _playerKeys2;

	void _initSettings(const std::string &pName1, const std::string &pName2, const std::vector<int> &pKey1, const std::vector<int> &pKey2);
	void _backSettingsToDef();
	void _saveSettingsToConfig();
	void _initMenu();
	void _initAuthors();
	void onClickTF(Event* ev);
	void onEvent(Event* ev);
	void onComplete(Event* ev);
	void onTweenDone(Event* ev);
	void onKeyEvent(Event* ev);
	void onCloseEvent(Event* ev);
	void _initEngineEffects();
	void _initFireBottomEffects();
	void _initSmokeBottomEffects();
	void _initSparksTopEffects();
public:
	static const short MENU_MAIN     = 0;
	static const short MENU_SETTINGS = 1;
	static const short MENU_AUTHORS  = 2;
	static const short TASK_CANCEL   = 10;
	static const short TASK_SAVE     = 11;

	MenuState();
	static spMenuState instance;
	Tween::EASE _ease;
	spActor _easeGraph;
};