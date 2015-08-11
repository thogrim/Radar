#include "SpriteEntity.h"

SpriteEntity::SpriteEntity(const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues)
	:Entity(velocity,acceleration,maxVelocity,accValues),
	sprite_(){
}

SpriteEntity::SpriteEntity(float vx, float vy, float ax, float ay, float maxVx, float maxVy, float accValueX, float accValueY)
	: SpriteEntity(sf::Vector2f(vx, vy), sf::Vector2f(ax, ay), sf::Vector2f(maxVx, maxVy), sf::Vector2f(accValueX, accValueY)){
}

SpriteEntity::SpriteEntity()
	: SpriteEntity(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f){
}

SpriteEntity::~SpriteEntity(){
}

void SpriteEntity::setTexture(const sf::Texture& texture){
	sprite_.setTexture(texture);
	sprite_.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
}

void SpriteEntity::centerOrigin(){
	sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
}

void SpriteEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	target.draw(sprite_, states);
}