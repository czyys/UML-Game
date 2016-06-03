#pragma once
#include "oxygine-framework.h"
#include "../res"
#include <string>

using namespace oxygine;

DECLARE_SMART(TextField, spTextField);

class InputField : public Sprite {
private:
	bool _isLabel;
	spTextField _labelField;
	spTextField _textField;
	std::string _text;
	std::string _startText;
	void _init(const std::string& text, const bool &longField);
public:
	InputField();
	InputField(const int &keyCode, const bool &longField);
	InputField(const std::string &startText, const bool &longField);
	void changeSize(const Vector2& size);
	void updateTextField();
	void addLabel(const std::string &text);
	void addLabel(const std::string &text, const int &size);
	bool removeLabel();
	void moveLabel(const Vector2 &position);
	spTextField getTextField() const;
	std::string getText() const;
};