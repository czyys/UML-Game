#include "SimpleButton.h"

SimpleButton::SimpleButton(){
	_init("btnn");
}

SimpleButton::SimpleButton(const char* textureName){
	_init(textureName);
}

void SimpleButton::_init(const char* textureName){
	_textField = new TextField();
	_textField->setTouchEnabled(false);
	_textField->setFontSize2Scale(14);
	_textField->setColor(Color(0, 255, 156));
	_textField->attachTo(this);

	this->setResAnim(GameResource::ui.getResAnim(textureName));
}

void SimpleButton::setText(const char* text){
	this->setText(text, SimpleButton::BUTTON_CENTER);
}

void SimpleButton::setText(const char* text, const int &position){
	_textField->setText(text);
	_textField->setY((this->getHeight() / 2.0f - _textField->getTextRect().getHeight() / 2.0f) - 2);
	
	switch (position) {
	case SimpleButton::BUTTON_LEFT:
		break;
	case SimpleButton::BUTTON_RIGHT:
		break;
	case SimpleButton::BUTTON_CENTER:
	default:
		_textField->setX(this->getWidth() / 2.0f - _textField->getTextRect().getWidth() / 2.0f);
		
		break;
	}
}

void SimpleButton::changeColor(const Color &c) {
	this->_textField->setColor(c);
}

std::string SimpleButton::getText() const{
	return _textField->getText();
}

void SimpleButton::onEvent(Event* ev){
	TouchEvent* event = static_cast<TouchEvent*>(ev);
	if (ev->type == TouchEvent::TOUCH_DOWN)
		setColor(Color::DarkCyan);

	if (ev->type == TouchEvent::TOUCH_UP)
		setColor(Color::White);
}