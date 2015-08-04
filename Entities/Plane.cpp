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

float Plane::countAngleDifferrence(){
	float angle1 = 180.f + atan2(destination_.y - getWorldPosition().y, destination_.x - getWorldPosition().x)*180.f / PI;
	angle1 < 90.f ? angle1 += 270.f : angle1 -= 90.f;
	float angle2 = angle1 - getRotation();
	return angle2;
}

void Plane::setDestination(const sf::Vector2i& destination){
	hasDestination_ = true;
	destination_ = static_cast<sf::Vector2f>(destination);
	//start heading towards destination
	float angleDifference = countAngleDifferrence();
	if ((angleDifference > 0.f && angleDifference < 180.f) || (angleDifference > -360.f && angleDifference < -180.f)){
		velocity_.y = maxVelocity_.y;
	}
	else if ((angleDifference > -180.f && angleDifference < 0.f) || (angleDifference > 180.f&&angleDifference < 360.f)){
		velocity_.y = -maxVelocity_.y;
	}
}

void Plane::update(const sf::Time& dt){
	if (hasDestination_){
		float angleDifference = abs(countAngleDifferrence());
		if (angleDifference < 1.f){
			velocity_.y = 0.f;
			hasDestination_ = false;
		}
	}
	//calculate offset
	float angle = -getRotation() +90.f;
	float vx = velocity_.x*cos(angle*PI / 180.f);
	float vy = -velocity_.x*sin(angle*PI / 180.f);
	//move
	rotate(velocity_.y*dt.asSeconds());
	move(vx*dt.asSeconds(), vy*dt.asSeconds());

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