/*
	TODO:
*/
#pragma once

#include "../SceneNode.h"

class Entity: public SceneNode{
protected:
	sf::Sprite sprite_;
	sf::Vector2f velocity_;		//current velocity
	sf::Vector2f acceleration_;	//current acceleration
	sf::Vector2f maxVelocity_;	//max velocity
	sf::Vector2f accValues_;	//values at which entity accelerates

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(const sf::Time& dt);
	void adjustVelocity(); //adjusts velocity so it does not exceed max velocity
public:
	Entity(const sf::Texture& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues);
	Entity(const sf::Texture& texture, const float vx, const float vy, const float ax, const float ay, const float maxVx, const float maxVy, const float accValueX, const float accValueY);
	Entity(const sf::Texture& texture);
	Entity();
	virtual ~Entity();
	
	void setTexture(const sf::Texture& texture);
	void centerOrigin();
	void setVelocity(const sf::Vector2f& velocity);
	void setVelocity(const float vx, const float vy);
	void adjustMaxVelocity();
	void setMaxVelocity(const sf::Vector2f& maxVelocity);
	void setMaxVelocity(const float vx, const float vy);
	void setAcceleration(const sf::Vector2f& acceleration);
	void setAcceleration(const float ax, const float ay);
	void setAccelerationValues(const sf::Vector2f& accValues);
	void setAccelerationValues(const float xVal, const float yVal);

	virtual void create(const sf::Texture& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues);
	virtual void create(const sf::Texture& texture, const float vx, const float vy, const float ax, const float ay, const float maxVx, const float maxVy, const float accValueX, const float accValueY);
};