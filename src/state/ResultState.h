#include "State.h"
#include "../display/InputField.h"
#include "../resource/GameResource.h"

DECLARE_SMART(ResultState, spResultState);

class ResultState : public State {
private:
	spSprite     _resultMode;
	void onEvent(Event* ev);
	void _initResult();
	short _nextState;
	short _task;

public:
	ResultState();
	static spResultState instance;
	Tween::EASE _ease;
	spActor _easeGraph;

};