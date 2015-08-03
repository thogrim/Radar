#include "Plane.h"

Plane::Plane(const sf::Texture& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues)
	:Entity(texture, velocity, acceleration, maxVelocity, accValues),
	hovered_(false),
	selected_(false),
	hasDestination_(false),
	destination_(0.f, 0.f),
	hoveredRect_(),
	selectedRect_(),
	selectionSprite_(){
}

Plane::Plane(const sf::Texture& texture, const float vx, const float vy, const float ax, const float ay, const float maxVx, const float maxVy, const float accValueX, const float accValueY)
	:Plane(texture, sf::Vector2f(vx, vy), sf::Vector2f(ax, ay), sf::Vector2f(maxVx, maxVy), sf::Vector2f(accValueX, accValueY)){
}

Plane::Plane()
	: Entity(),
	selected_(false),
	hasDestination_(false),
	destination_(0.f, 0.f),
	hoveredRect_(),
	selectedRect_(),
	selectionSprite_(){
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

bool Plane::hover(const sf::Vector2i& mousePos){
	sf::Vector2i distance = static_cast<sf::Vector2i>(getWorldPosition()) - mousePos;
	hovered_ = (sqrt(pow(distance.x, 2) + pow(distance.y, 2))) < 30;
	//if (hovered_)
	//	selectionSprite_.setTextureRect(hoveredRect_);
	return hovered_;
}

bool Plane::select(){
	if (hovered_){
		selected_ = true;
		return true;
	}
	else
		return false;
}

bool Plane::unselect(){
	if (selected_){
		selected_ = false;
		return true;
	}
	else
		return false;
}

void Plane::setDestination(const sf::Vector2i& destination){
	hasDestination_ = true;
	destination_ = static_cast<sf::Vector2f>(destination);
	//start heading towards destination
	//sf::Vector2i pos = static_cast<sf::Vector2i>(getWorldPosition());
	float angle1 = 180.f+atan2(destination.y - getWorldPosition().y, destination.x - getWorldPosition().x)*180.f / PI;
	angle1 < 90.f ? angle1 += 270.f : angle1 -= 90.f;
	float angle2 = angle1-getRotation();
	if ((angle2>0.f&&angle2<180.f) || (angle2>-360.f&&angle2 < -180.f))
		velocity_.y = maxVelocity_.y;
	else
		velocity_.y = -maxVelocity_.y;
	//getWorldPosition().x > destination_.x ? acceleration_.y = accValues_.y : acceleration_.y = -accValues_.y;
}

void Plane::update(const sf::Time& dt){
	//calculate offset
	float angle = -getRotation() +90.f;
	float vx = velocity_.x*cos(angle*PI / 180.f);
	float vy = -velocity_.x*sin(angle*PI / 180.f);
	rotate(velocity_.y*dt.asSeconds());
	move(vx*dt.asSeconds(), vy*dt.asSeconds());

	if (hasDestination_){
		//TODO

	}

	//selection sprite update
	if (hovered_)
		selectionSprite_.setTextureRect(hoveredRect_);
	else if (selected_)
		selectionSprite_.setTextureRect(selectedRect_);
	else
		selectionSprite_.setTextureRect(sf::IntRect(0, 0, 0, 0));
}

void Plane::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(sprite_, states);
	target.draw(selectionSprite_, states);
}