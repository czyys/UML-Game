#include "oxygine-framework.h"
#include "../resource/GameResource.h"
#include <string>

using namespace oxygine;

class TextNameField : public Sprite {
private:
	bool _isLabel;
	spTextField _labelField;
	spTextField _textField;
	std::string _text;
	std::string _startText;
public:
	TextNameField();
	void addLabel(const std::string &text);
	spTextField getTextField() const;
	std::string getText() const;
};