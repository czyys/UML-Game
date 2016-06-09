#include "State.h"
#include "../display/InputField.h"
#include "../resource/GameResource.h"

DECLARE_SMART(ResultState, spResultState);

class ResultState : public State {
private:
	spSprite    _resultMode;

	void onEvent(Event* ev);
	void _initResult();
public:
	static spResultState instance;
	
	ResultState();
	Tween::EASE _ease;
	spActor _easeGraph;
};