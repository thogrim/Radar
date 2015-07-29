#include "Component.h"

using namespace GUI;

Component::Component(const sf::Texture& texture, const float posX, const float posY, const int nSprites, const std::function<void()>& action, sf::Vector2f parentPos)
	:hovered_(false),
	pressed_(false),
	sprite_(),
	nSprites_(nSprites),
	textureRect_(0, 0, texture.getSize().x, texture.getSize().y / nSprites_),
	action_(action),
	parentPos_(parentPos){
	setPosition(posX, posY);
	sprite_.setTexture(texture);
	setSprite(1);
}

Component::Component(const sf::Texture& texture, const float posX, const float posY, const int nSprites, const std::function<void()>& action, const float parentPosX, const float parentPosY)
	:Component(texture,posX,posY,nSprites,action, sf::Vector2f(parentPosX,parentPosY)){
}

Component::Component(const sf::Texture& texture, const float posX, const float posY, const int nSprites)
	:Component(texture, posX, posY, nSprites, [](){}, sf::Vector2f(0,0)){
}
Component::~Component(){
}

bool Component::hoveredNow(const sf::Vector2i& mousePos){
	sf::Vector2f pos(getTransform()*sf::Vector2f());
	sf::Vector2f size(textureRect_.width, textureRect_.height);
	sf::FloatRect rect(pos.x+parentPos_.x, pos.y+parentPos_.y, size.x, size.y);
	hovered_ = rect.contains(static_cast<sf::Vector2f>(mousePos));
	return hovered_;
}

void Component::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	target.draw(sprite_, states);
}