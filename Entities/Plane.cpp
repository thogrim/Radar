#include "Plane.h"

Plane::Plane(const sf::Vector2f& velocity, float hitboxRadius, const sf::Texture& texture)
	:SpriteEntity(velocity, sf::Vector2f(0.f, 0.f), velocity, sf::Vector2f(0.f, 0.f)),
	hovered_(false),
	selected_(false),
	hasDestination_(false),
	destination_(0.f, 0.f),
	selection_(),
	hitboxRadius_(hitboxRadius){
	setTexture(texture);
	centerOrigin();
	selection_.setRadius(hitboxRadius_);
	selection_.setOutlineThickness(-3);
	selection_.setFillColor(sf::Color::Transparent);
	selection_.setOrigin(sf::Vector2f(hitboxRadius,hitboxRadius));
}

Plane::Plane(float vx, float vy, float hitboxRadius, const sf::Texture& texture)
	:Plane(sf::Vector2f(vx, vy), hitboxRadius, texture){
}

Plane::Plane(const sf::Texture& texture)
	: Plane(0.f, 0.f, 0.f, texture){
}

Plane::~Plane(){
}

void Plane::setHitboxRadius(float radius){
	hitboxRadius_ = radius;
	selection_.setRadius(hitboxRadius_); 
	selection_.setOrigin(sf::Vector2f(radius, radius));
}

bool Plane::selected() const{
	return selected_;
}

bool Plane::hovered() const{
	return  hovered_;
}

bool Plane::hover(const sf::Vector2i& mousePos){
	sf::Vector2i distance = static_cast<sf::Vector2i>(getPosition()) - mousePos;
	hovered_ = (sqrt(pow(distance.x, 2) + pow(distance.y, 2))) < hitboxRadius_;
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

void Plane::unselect(){
	selected_ = false;
}

float Plane::countAngleDifferrence(){
	float angle1 = 180.f + atan2(destination_.y - getPosition().y, destination_.x - getPosition().x)*180.f / PI;
	angle1 < 90.f ? angle1 += 270.f : angle1 -= 90.f;
	float angle2 = angle1 - getRotation();
	return angle2;
}

void Plane::setDestination(const sf::Vector2i& destination){
	hasDestination_ = true;
	destination_ = static_cast<sf::Vector2f>(destination);
	//start heading towards destination
	float angleDifference = countAngleDifferrence();
	if ((angleDifference > 0.f && angleDifference < 180.f) || (angleDifference > -360.f && angleDifference < -180.f))
		velocity_.y = maxVelocity_.y;
	else if ((angleDifference > -180.f && angleDifference < 0.f) || (angleDifference > 180.f&&angleDifference < 360.f))
		velocity_.y = -maxVelocity_.y;
	velocity_.x = maxVelocity_.x;
}

void Plane::update(const sf::Time& dt){
	if (hasDestination_){
		float angleDifference = abs(countAngleDifferrence());
		if (angleDifference < 1.f){
			velocity_.y = 0.f;
			hasDestination_ = false;
		}
	}

	//stop moving when destination is reached
	if (abs((getPosition() - destination_).x) < 5.f &&
		abs((getPosition() - destination_).y) < 5.f)
		setVelocity(0.f, 0.f);

	//calculate offset
	float angle = -getRotation() +90.f;
	float vx = velocity_.x*cos(angle*PI / 180.f);
	float vy = -velocity_.x*sin(angle*PI / 180.f);
	//move
	rotate(velocity_.y*dt.asSeconds());
	move(vx*dt.asSeconds(), vy*dt.asSeconds());

	//selection sprite update
	if (selected_)
		selection_.setOutlineColor(sf::Color(43, 212, 52));
	else if (hovered_)
		selection_.setOutlineColor(sf::Color(217, 255, 0));
}

void Plane::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	target.draw(sprite_, states);
	if (selected_ || hovered_)
		target.draw(selection_, states);
}