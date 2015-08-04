#include "CheckBox.h"

using namespace GUI;

//Checkbox::Checkbox(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action, const std::function<void()>& secondAction, const sf::Vector2f& parentPos)
//	:Component(texture,posX,posY,6,action,parentPos),
//	secondAction_(secondAction),
//	toggled_(false){
//}
//
//Checkbox::Checkbox(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action, const std::function<void()>& secondAction, const float parentPosX, const float parentPosY)
//	:Checkbox(texture,posX,posY,action,secondAction,sf::Vector2f(parentPosX,parentPosY)){
//}
//
//Checkbox::Checkbox(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action, const std::function<void()>& secondAction)
//	: Checkbox(texture, posX, posY, action, secondAction, sf::Vector2f(0, 0)){
//}

Checkbox::Checkbox()
	:Component(6),
	toggled_(false),
	toggleAction_(),
	untoggleAction_(){
}

Checkbox::~Checkbox(){
}

void Checkbox::setToggleAction(const std::function<void()>& action){
	toggleAction_ = action;
}

void Checkbox::setUntoggleAction(const std::function<void()>& action){
	untoggleAction_ = action;
}

bool Checkbox::press(){
	if (hovered_){
		pressed_ = true;
		toggled_ ? setSprite(Sprite::PRESSED_TOGGLED) : setSprite(Sprite::PRESSED_NOT_TOGGLED);
		return true;
	}
	else
		return false;
}

bool Checkbox::release(){
	pressed_ = false;
	if (hovered_){
		toggled_ = !toggled_;
		return true;
	}
	else
		return false;
}

const std::function<void()> Checkbox::getAction() const{
	return toggled_ ? untoggleAction_ : toggleAction_;
}

void Checkbox::performAction() const{
	toggled_ ? toggleAction_() : untoggleAction_();
}

void Checkbox::update(const sf::Vector2i& mousePos){
	hoveredNow(mousePos);
	if (!hovered_)
		toggled_ ? setSprite(Sprite::TOGGLED) : setSprite(Sprite::NOT_TOGGLED);
	else{
		if (!pressed_)
			toggled_ ? setSprite(Sprite::HOVERED_TOGGLED) : setSprite(Sprite::HOVERED_NOT_TOGGLED);
		else
			toggled_ ? setSprite(Sprite::PRESSED_TOGGLED) : setSprite(Sprite::PRESSED_NOT_TOGGLED);
	}
}
