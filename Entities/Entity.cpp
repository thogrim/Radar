#include "Entity.h"

Entity::Entity(/*const sf::Texture& texture, */const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues)
	:/*SceneNode(),*/
	//sprite_(),
	velocity_(velocity),
	acceleration_(acceleration),
	maxVelocity_(sf::Vector2f(abs(maxVelocity.x), abs(maxVelocity.y))),
	accValues_(accValues),
	toDestroy_(false){
	//sprite_.setTexture(texture);
}

Entity::Entity(/*const sf::Texture& texture, */float vx, float vy, float ax, float ay, float maxVx, float maxVy, float accValueX, float accValueY)
	:Entity(/*texture, */sf::Vector2f(vx, vy), sf::Vector2f(ax, ay), sf::Vector2f(maxVx, maxVy), sf::Vector2f(accValueX, accValueY)){
}

//Entity::Entity(const sf::Texture& texture)
//	:Entity(texture, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f){
//}

Entity::Entity()
	: Entity(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f){
}

//Entity::Entity(const Entity& e)
//	:SceneNode(e),
//	sprite_(e.sprite_),
//	velocity_(e.velocity_),
//	acceleration_(e.acceleration_),
//	accValues_(e.accValues_){
//	setPosition(e.getPosition());
//}

Entity::~Entity(){
	std::cout << "entity destroyed\n";
}

//void Entity::create(const sf::Texture& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues){
//	sprite_.setTexture(texture);
//	sprite_.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
//	velocity_ = sf::Vector2f(velocity);
//	acceleration_ = sf::Vector2f(acceleration);
//	maxVelocity_ = sf::Vector2f(maxVelocity);
//}

//void Entity::create(const sf::Texture& texture, float vx, float vy, float ax, float ay, float maxVx, float maxVy, float accValueX, float accValueY){
//	sprite_.setTexture(texture);
//	sprite_.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
//	velocity_ = sf::Vector2f(vx,vy);
//	acceleration_ = sf::Vector2f(ax,ay);
//	maxVelocity_ = sf::Vector2f(maxVx,maxVy);
//	accValues_ = sf::Vector2f(accValueX, accValueY);
//}

//void Entity::setTexture(const sf::Texture& texture){
//	sprite_.setTexture(texture);
//	sprite_.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
//}
//
//void Entity::centerOrigin(){
//	sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
//}

void Entity::setVelocity(const sf::Vector2f& velocity){
	velocity_ = velocity;
}

void Entity::setVelocity(float vx, float vy){
	velocity_ = sf::Vector2f(vx, vy);
}

void Entity::adjustMaxVelocity(){
	if (abs(velocity_.x) > maxVelocity_.x)
		maxVelocity_.x = abs(velocity_.x);
	if (abs(velocity_.y) > maxVelocity_.y)
		maxVelocity_.y = abs(velocity_.y);
}

void Entity::setMaxVelocity(const sf::Vector2f& maxVelocity){
	maxVelocity_ = maxVelocity;
}

void Entity::setMaxVelocity(float vx, float vy){
	maxVelocity_ = sf::Vector2f(vx, vy);
}

void Entity::setAcceleration(const sf::Vector2f& acceleration){
	acceleration_ = acceleration;
}

void Entity::setAcceleration(float ax, float ay){
	acceleration_ = sf::Vector2f(ax, ay);
}

void Entity::setAccelerationValues(const sf::Vector2f& accValues){
	accValues_ = accValues;
}

void Entity::setAccelerationValues(float xVal, float yVal){
	accValues_ = sf::Vector2f(xVal, yVal);
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

bool Entity::toDestroy() const{
	return toDestroy_;
}

void Entity::destroy(){
	toDestroy_ = true;
}

void Entity::update(const sf::Time& dt){
	//moving in Cartesian coordinate system 
	velocity_ += acceleration_*dt.asSeconds();
	adjustVelocity();
	move(velocity_*dt.asSeconds());
}

//void Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
//	target.draw(sprite_, states);
//}
