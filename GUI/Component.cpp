#include "Component.h"

using namespace GUI;

//Component::Component(const sf::Texture& texture, const float posX, const float posY, const int nSprites, const std::function<void()>& action, sf::Vector2f parentPos)
//	:hovered_(false),
//	pressed_(false),
//	sprite_(),
//	nSprites_(nSprites),
//	textureRect_(0, 0, texture.getSize().x, texture.getSize().y / nSprites_),
//	action_(action),
//	parentPos_(parentPos){
//	setPosition(posX, posY);
//	sprite_.setTexture(texture);
//	setSprite(1);
//}
//
//Component::Component(const sf::Texture& texture, const float posX, const float posY, const int nSprites, const std::function<void()>& action, const float parentPosX, const float parentPosY)
//	:Component(texture,posX,posY,nSprites,action, sf::Vector2f(parentPosX,parentPosY)){
//}
//
//Component::Component(const sf::Texture& texture, const float posX, const float posY, const int nSprites)
//	:Component(texture, posX, posY, nSprites, [](){}, sf::Vector2f(0,0)){
//}

Component::Component(const int nSprites)
	:active_(true),
	hovered_(false),
	pressed_(false),
	//text_(),
	sprite_(),
	nSprites_(nSprites),
	textureRect_(0,0,0,0),
	parentPos_(0,0){	
}

Component::~Component(){
}

void Component::setTexture(const sf::Texture& texture){
	sprite_.setTexture(texture);
	textureRect_ = sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y / nSprites_);
	sprite_.setTextureRect(textureRect_);
}

void Component::setSprite(const int nSprite){
	assert(nSprite <= nSprites_ && nSprite > 0);
	sprite_.setTextureRect(sf::IntRect(0, (nSprite - 1)*textureRect_.height, textureRect_.width, textureRect_.height));
}

//void Component::setText(const std::string& string, const sf::Font font, unsigned int characterSize){
//	text_.setString(string);
//	text_.setFont(font);
//	text_.setCharacterSize(characterSize);
//}

//void Component::setText(const sf::Text& text){
//	text_ = text;
//	text_.setPosition(parentPos_+getPosition()+text.getPosition());
//}

//void Component::setTextColor(const sf::Color& color){
//	text_.setColor(color);
//}

//void Component::setFont(const sf::Font& font){
//	text_.setFont(font);
//}
//
//void Component::setString(const std::string& string){
//	text_.setString(string);
//}

//void Component::setTextPosition(float x, float y){
//	text_.setPosition(getPosition().x+x, getPosition().y+y);
//}

void Component::setParentPosition(const sf::Vector2f& parentPos){
	parentPos_ = parentPos;
}

void Component::setActive(bool active){
	active_ = active;
}

bool Component::isActive() const{
	return active_;
}

bool Component::hoveredNow(const sf::Vector2i& mousePos){
	sf::Vector2f pos(getTransform()*sf::Vector2f());
	sf::Vector2f size(textureRect_.width, textureRect_.height);
	sf::FloatRect rect(pos.x+parentPos_.x, pos.y+parentPos_.y, size.x, size.y);
	hovered_ = rect.contains(static_cast<sf::Vector2f>(mousePos));
	return hovered_;
}

bool Component::hovered() const{
	return hovered_;
}

bool Component::pressed() const{
	return pressed_;
}

void Component::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	target.draw(sprite_, states);
	//target.draw(text_);
	/*states.transform *= text_.getTransform();
	target.draw(text_, states);*/
}