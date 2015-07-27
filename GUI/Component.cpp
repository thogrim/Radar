#include "Component.h"

using namespace GUI;

Component::Component(const sf::Texture& texture, const float posX, const float posY, const int nSprites)
	:hovered_(false),
	pressed_(false),
	sprite_(),
	nSprites_(nSprites),
	textureRect_(0, 0, texture.getSize().x, texture.getSize().y / nSprites_){
	setPosition(posX, posY);
	sprite_.setTexture(texture);
	setSprite(1);
}

//Component::Component() 
//	:{
//}

Component::~Component(){
}

void Component::hoveredNow(const sf::Vector2i& mousePos){
	sf::Vector2f pos(getTransform()*sf::Vector2f());
	sf::Vector2f size(textureRect_.width, textureRect_.height);
	sf::FloatRect rect(pos.x, pos.y, size.x, size.y);
	hovered_ = rect.contains(static_cast<sf::Vector2f>(mousePos));
}

void Component::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	target.draw(sprite_, states);
}