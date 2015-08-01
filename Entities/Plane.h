/*
	TODO:
	in setDestination method check if it is possible to reach destination

	fix the rotation
*/
#pragma once

#include "Entity.h"

const float PI = 3.14159265f;

class Plane: public Entity{
private:
	/*
		Plane's velocity and acceleration values
		are in polar coordinate system!
	*/
	bool targeted_;
	bool hasDestination_;
	sf::Vector2f destination_;
public:
	Plane(const sf::Texture& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues);
	Plane(const sf::Texture& texture, const float vx, const float vy, const float ax, const float ay, const float maxVx, const float maxVy, const float accValueX, const float accValueY);
	Plane();
	~Plane();

	bool targeted() const{
		return targeted_;
	}

	//virtual void create(const sf::Texture& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues);
	//virtual void create(const sf::Texture& texture, const float vx, const float vy, const float ax, const float ay, const float maxVx, const float maxVy, const float accValueX, const float accValueY);
	void setDestination(const sf::Vector2i& destination);
	void update(const sf::Time& dt);
};