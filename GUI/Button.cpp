#include "Button.h"

using namespace GUI;

Button::Button(const sf::Texture& texture, const float posX, const float posY)
	:Component(texture,posX,posY,3)
	//component stuff
	//hovered_(false),
	//pressed_(false),
	//sprite_(),
	//nSprites_(3),
	//textureRect_(0, 0, texture.getSize().x, texture.getSize().y / nSprites_),
	///////
	//action_(action)
{
	//setPosition(posX, posY);
	//sprite_.setTexture(texture);
	//setSprite(1);
}

//Button::Button()
//	:hovered_(false),
//	pressed_(false),
//	action_(){
//}

Button::~Button(){
}

//void Button::hoveredNow(const sf::Vector2i& mousePos){
//	sf::Vector2f pos(getTransform()*sf::Vector2f());
//	sf::Vector2f size(sprite_.getTextureRect().width, sprite_.getTextureRect().height);
//	sf::FloatRect rect(pos.x, pos.y, size.x, size.y);
//	hovered_ = rect.contains(static_cast<sf::Vector2f>(mousePos));
//}

//void Button::processEvents(const sf::Event& ev){
//
//}

void Button::update(const sf::Vector2i& mousePos){
	hoveredNow(mousePos);
	if (hovered_ && !pressed_)
		setSprite(Sprite::HOVERED);
	else if (!hovered_)
		setSprite(Sprite::NORMAL);
}

//void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
//	states.transform *= getTransform();
//	target.draw(sprite_, states);
//}