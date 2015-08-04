#include "Button.h"

using namespace GUI;

//Button::Button(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action, const sf::Vector2f& parentPos)
//	:Component(texture,posX,posY,3,action,parentPos){
//}
//
//Button::Button(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action, const float parentPosX, const float parentPosY)
//	:Button(texture, posX, posY, action, sf::Vector2f(parentPosX, parentPosY)){
//}
//
//Button::Button(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action)
//	: Button(texture, posX, posY, action, sf::Vector2f(0, 0)){
//}

Button::Button()
	:Component(3),
	action_(){
}

Button::~Button(){
}

void Button::setAction(const std::function<void()>& action){
	action_ = action;
}

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