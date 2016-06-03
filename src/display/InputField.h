#pragma once
#include "oxygine-framework.h"
#include "../resource/GameResource.h"
#include <string>

using namespace oxygine;

DECLARE_SMART(InputField, spInputField);

class InputField : public Sprite {
protected:
	bool _isLabel;
	bool _isLong;
	int  _maxKeyLength;
	spTextField _labelField;
	spTextField _textField;
	std::string _text;
	std::string _startText;
	Color       _focusColor;
	Color       _stdColor;
	void _init(const std::string& text, const bool &longField);
public:
	InputField();
	InputField(const int &keyCode, const bool &longField);
	InputField(const std::string &startText, const bool &longField);
	
	void changeSize(const Vector2& size);
	void updateTextField();
	void addLabel(const std::string &text);
	void addLabel(const std::string &text, const int &size);
	void setMaxKeyLength(const int &maxLength);
	void setContentText(const std::string &text);
	void setContentText(const int &keyCode);
	void focus(const bool &isFocus);
	int getMaxKeyLength() const;
	bool removeLabel();
	void moveLabel(const Vector2 &position);
	bool isLongField() const;
	spTextField getTextField() const;
	std::string getText() const;
};