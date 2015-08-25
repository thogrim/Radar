#include "Plane.h"

Plane::Plane(const sf::Vector2f& velocity, float hitboxRadius, const sf::Texture& texture)
	:SpriteEntity(velocity, sf::Vector2f(0.f, 0.f), velocity, sf::Vector2f(0.f, 0.f)),
	hovered_(false),
	selected_(false),
	hasDestination_(false),
	tempDestination_(0.f, 0.f),
	selection_(),
	hitboxRadius_(hitboxRadius),
	visible_(true),
	endDestination_(0.f,0.f),
	reachedDestination_(false),
	collectedPoints_(0.f),
	lifetime_(sf::seconds(50.f)),
	timePassed_(sf::Time::Zero){
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

void Plane::setLifetime(float lifetime){
	lifetime_ = sf::seconds(lifetime);
}

void Plane::setHitboxRadius(float radius){
	hitboxRadius_ = radius;
	selection_.setRadius(hitboxRadius_); 
	selection_.setOrigin(sf::Vector2f(radius, radius));
}

const float Plane::getHitboxRadius() const{
	return hitboxRadius_;
}

void Plane::setVisibility(bool visible){
	visible_ = visible;
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
	float angle1 = 180.f + atan2(tempDestination_.y - getPosition().y, tempDestination_.x - getPosition().x)*180.f / PI;
	angle1 < 90.f ? angle1 += 270.f : angle1 -= 90.f;
	return angle1 - getRotation();
}

void Plane::setTempDestination(const sf::Vector2i& destination){
	hasDestination_ = true;
	tempDestination_ = static_cast<sf::Vector2f>(destination);
	//start heading towards destination
	float angleDifference = countAngleDifferrence();
	if ((angleDifference > 0.f && angleDifference < 180.f) || (angleDifference > -360.f && angleDifference < -180.f))
		velocity_.y = maxVelocity_.y;
	else if ((angleDifference > -180.f && angleDifference < 0.f) || (angleDifference > 180.f&&angleDifference < 360.f))
		velocity_.y = -maxVelocity_.y;
	velocity_.x = maxVelocity_.x;
}

void Plane::setEndDestination(float x, float y){
	endDestination_.x = x;
	endDestination_.y = y;
}

bool Plane::reachedDestination() const{
	return reachedDestination_;
}

void Plane::collectPoints(float points){
	collectedPoints_ += points;
}

float Plane::takePoints(){
	float p = collectedPoints_;
	collectedPoints_ = 0.f;
	return p;
}

void Plane::update(const sf::Time& dt){
	//fuel update
	timePassed_ += dt;
	if (timePassed_ > lifetime_)
		toDestroy_ = true;

	//check if endDestination is reached
	if (sqrt(pow(getPosition().x - endDestination_.x, 2) + pow(getPosition().y - endDestination_.y, 2)) < 10.f){
		reachedDestination_ = true;
		collectedPoints_ += 100.f;
	}
	
	//stop rotating when heading towards dest
	if (hasDestination_ && velocity_.y!=0.f){
		float angleDifference = countAngleDifferrence();
		if (abs(angleDifference) < 1.f){
			rotate(angleDifference);
			velocity_.y = 0.f;
			//hasDestination_ = false;
		}
	}

	//stop moving when destination is reached
	if (abs((getPosition() - tempDestination_).x) < 5.f &&
		abs((getPosition() - tempDestination_).y) < 5.f){
		setVelocity(0.f, 0.f);
		hasDestination_ = false;
	}

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

void Plane::drawTempDestination(sf::RenderTarget& target/*, sf::RenderStates states*/) const{
	if (hasDestination_){
		sf::Vertex line[] = {
			sf::Vertex(getPosition()),
			sf::Vertex(tempDestination_)
		};
		float crossSize = 15;
		sf::Vertex cross1[] = {
			sf::Vertex(tempDestination_ - sf::Vector2f(crossSize, crossSize)),
			sf::Vertex(tempDestination_ + sf::Vector2f(crossSize, crossSize))
		};
		sf::Vertex cross2[] = {
			sf::Vertex(tempDestination_ - sf::Vector2f(crossSize, -crossSize)),
			sf::Vertex(tempDestination_ + sf::Vector2f(crossSize, -crossSize))
		};
		target.draw(line, 2, sf::Lines);
		target.draw(cross1, 2, sf::Lines);
		target.draw(cross2, 2, sf::Lines);
	}
}

void Plane::drawEndDestination(sf::RenderTarget& target) const{
	//this is temporary version
	/*float size = 20;
	sf::RectangleShape shape1(sf::Vector2f(size / 4, size / 2));
	shape1.setOrigin(size / 8, -size / 2);
	shape1.setPosition(endDestination_);
	shape1.setFillColor(sf::Color(0, 255, 0));
	sf::CircleShape shape2(size / 3, 3);
	shape2.setOrigin(size / (2 * sqrt(3)), 0.f);
	shape2.setPosition(endDestination_);
	shape2.setFillColor(sf::Color(0, 255, 0));
	if (endDestination_.x == 800.f){
		shape1.rotate(90.f);
		shape2.rotate(90.f);
	}
	else if (endDestination_.x == 0.f){
		shape1.rotate(-90.f);
		shape2.rotate(-90.f);
	}
	else if (endDestination_.y == 600.f){
		shape1.rotate(180.f);
		shape2.rotate(180.f);
	}
	target.draw(shape1);
	target.draw(shape2);*/

	sf::CircleShape endDest(10, 4);
	endDest.setFillColor(sf::Color(255, 0, 255));
	endDest.setPosition(endDestination_);
	endDest.setOrigin(5, 5);
	target.draw(endDest);
}

void Plane::drawFuel(sf::RenderTarget& target) const{
	float fuelBar = 50.f;
	sf::RectangleShape fuel(sf::Vector2f(fuelBar, 5));
	fuel.setPosition(getPosition());
	fuel.setOrigin(fuelBar / 2, hitboxRadius_ + 10);
	fuel.setFillColor(sf::Color(255, 0, 0));
	fuel.setOutlineThickness(1);
	fuel.setOutlineColor(sf::Color(0, 0, 0));
	sf::RectangleShape remainingFuel(sf::Vector2f(fuelBar*(1.f - timePassed_ / lifetime_), 5));
	remainingFuel.setPosition(getPosition() - fuel.getOrigin());
	remainingFuel.setFillColor(sf::Color(0, 255, 0));
	target.draw(fuel);
	target.draw(remainingFuel);
}

void Plane::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	//drawing tempDestination and endDestination
	if (selected_){
		drawTempDestination(target);
		drawEndDestination(target);
	}

	states.transform *= getTransform();
	if (visible_){
		//drawing plane
		target.draw(sprite_, states);
		//drawing fuel
		drawFuel(target);
	}

	//drawing selection
	if (selected_ || hovered_)
		target.draw(selection_, states);
}

void Plane::accept(Visitor& c){
	//do nothing for now
	//c.visit(*this);
}