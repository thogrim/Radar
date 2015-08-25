#include "DebugEntity.h"

DebugEntity::DebugEntity(const sf::Texture& texture)
	:Plane(texture) {
}

DebugEntity::~DebugEntity(){
}

void DebugEntity::setTempDestination(const sf::Vector2i& destination){
	hasDestination_ = true;
	tempDestination_ = static_cast<sf::Vector2f>(destination);
	float angle = 180.f + atan2(tempDestination_.y - getPosition().y, tempDestination_.x - getPosition().x)*180.f / PI;
	angle < 90.f ? angle += 270.f : angle -= 90.f;
	setRotation(angle);
	velocity_.x = maxVelocity_.x;
}

void DebugEntity::update(const sf::Time& dt){
	if (hasDestination_){
		float angle = -getRotation() + 90.f;
		//float angle = getRotation();
		float vx = velocity_.x*cos(angle*PI / 180.f);
		float vy = -velocity_.x*sin(angle*PI / 180.f);
		move(vx*dt.asSeconds(), vy*dt.asSeconds());

		if (abs((getPosition() - tempDestination_).x) < 5.f &&
			abs((getPosition() - tempDestination_).y) < 5.f){
			velocity_.x = 0.f;
			hasDestination_ = false;
		}
	}

	if (selected_)
		selection_.setOutlineColor(sf::Color(43, 212, 52));
	else if (hovered_)
		selection_.setOutlineColor(sf::Color(217, 255, 0));
}