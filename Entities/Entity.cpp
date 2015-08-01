#include "Entity.h"

Entity::Entity(const sf::Texture& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues)
	:SceneNode(),
	sprite_(),
	velocity_(velocity),
	acceleration_(acceleration),
	accValues_(accValues){
	sprite_.setTexture(texture);
}

Entity::Entity(const sf::Texture& texture, const float vx, const float vy, const float ax, const float ay, const float maxVx, const float maxVy, const float accValueX, const float accValueY)
	:Entity(texture, sf::Vector2f(vx, vy), sf::Vector2f(ax, ay), sf::Vector2f(maxVx, maxVy), sf::Vector2f(accValueX, accValueY)){
}

Entity::Entity(const sf::Texture& texture)
	: Entity(texture, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f){
}

Entity::Entity()
	: Entity(sf::Texture()){
}

Entity::~Entity(){
}

void Entity::create(const sf::Texture& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues){
	sprite_.setTexture(texture);
	sprite_.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
	velocity_ = sf::Vector2f(velocity);
	acceleration_ = sf::Vector2f(acceleration);
	maxVelocity_ = sf::Vector2f(maxVelocity);
}

void Entity::create(const sf::Texture& texture, const float vx, const float vy, const float ax, const float ay, const float maxVx, const float maxVy, const float accValueX, const float accValueY){
	sprite_.setTexture(texture);
	sprite_.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
	velocity_ = sf::Vector2f(vx,vy);
	acceleration_ = sf::Vector2f(ax,ay);
	maxVelocity_ = sf::Vector2f(maxVx,maxVy);
	accValues_ = sf::Vector2f(accValueX, accValueY);
}

void Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(sprite_, states);
}

void Entity::adjustVelocity(){
	if (velocity_.x > maxVelocity_.x)
		velocity_.x = maxVelocity_.x;
	if (velocity_.y > maxVelocity_.y)
		velocity_.y = maxVelocity_.y;
	if (velocity_.x < -maxVelocity_.x)
		velocity_.x = -maxVelocity_.x;
	if (velocity_.y < -maxVelocity_.y)
		velocity_.y = -maxVelocity_.y;
}

void Entity::update(const sf::Time& dt){
	//moving in Cartesian coordinate system 
	velocity_ += acceleration_*dt.asSeconds();
	adjustVelocity();
	move(velocity_*dt.asSeconds());
}