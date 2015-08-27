#include "Button.h"

using namespace GUI;

Button::Button()
	:Component(3),
	action_(){
}

Button::~Button(){
}

void Button::setAction(const std::function<void()>& action){
	action_ = action;
}

//void Button::setText(const sf::Text& text){
//	text_ = text;
//	float xPos = parentPos_.x + getPosition().x + textureRect_.width / 2;
//	float yPos = parentPos_.y + getPosition().y + textureRect_.height / 2;
//	text_.setPosition(xPos,yPos);
//	text_.setOrigin(text_.getLocalBounds().width / 2, text_.getCharacterSize() * 5 / 8);
//}

bool Button::press(){
	if (hovered_){
		pressed_ = true;
		setSprite(Sprite::PRESSED);
		return true;
	}
	else
		return false;
}

bool Button::release(){
	if (pressed_){
		pressed_ = false;
		return hovered_ ? true : false;
	}
	else
		return false;
}

const std::function<void()> Button::getAction() const{
	return action_;
}

void Button::performAction() const{
	action_();
}

void Button::update(const sf::Vector2i& mousePos){
	hoveredNow(mousePos);
	if (hovered_ && !pressed_)
		setSprite(Sprite::HOVERED);
	else if (!hovered_)
		setSprite(Sprite::NORMAL);
}