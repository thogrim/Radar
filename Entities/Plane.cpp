#include "Plane.h"

Plane::Plane(const sf::Texture& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues)
	:Entity(texture,velocity,acceleration,maxVelocity,accValues),
	targeted_(false),
	hasDestination_(false),
	destination_(0.f,0.f)
	{
}

Plane::Plane(const sf::Texture& texture, const float vx, const float vy, const float ax, const float ay, const float maxVx, const float maxVy, const float accValueX, const float accValueY)
	:Plane(texture, sf::Vector2f(vx, vy), sf::Vector2f(ax, ay), sf::Vector2f(maxVx, maxVy), sf::Vector2f(accValueX,accValueY)){
}

Plane::Plane()
	: Entity(),
	targeted_(false),
	hasDestination_(false),
	destination_(0.f, 0.f){
}

Plane::~Plane(){
}

//void Plane::create(const sf::Texture& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues){
//	Entity::create(texture, velocity, acceleration, maxVelocity);
//	accValues_ = accValues;
//}
//
//void Plane::create(const sf::Texture& texture, const float vx, const float vy, const float ax, const float ay, const float maxVx, const float maxVy, const float accValueX, const float accValueY){
//	Entity::create(texture, vx,vy,ax,ay,maxVx,maxVy);
//	accValues_ = sf::Vector2f(accValueX,accValueY);
//}

void Plane::setDestination(const sf::Vector2i& destination){
	hasDestination_ = true;
	destination_ = static_cast<sf::Vector2f>(destination);
	//start heading towards destination
	getWorldPosition().x > destination_.x ? acceleration_.y = accValues_.y : acceleration_.y = -accValues_.y;
}

void Plane::update(const sf::Time& dt){
	if (hasDestination_){

	}
	//calculate offset
	float angle = -getRotation() + 90.f;
	float vx = velocity_.x*cos(angle*PI / 180.f);
	float vy = -velocity_.x*sin(angle*PI / 180.f);
	rotate(velocity_.y*dt.asSeconds());
	move(vx*dt.asSeconds(), vy*dt.asSeconds());
}