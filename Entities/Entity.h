/*
	TODO:
	try to split Entity class into movableEntity and targetableEntity
	and use multiple inheritance to create entities
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
	void adjustVelocity(); //adjust velocity so it does not exceed max velocity
public:
	Entity(const sf::Texture& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues);
	Entity(const sf::Texture& texture, const float vx, const float vy, const float ax, const float ay, const float maxVx, const float maxVy, const float accValueX, const float accValueY);
	Entity(const sf::Texture& texture);
	Entity();
	virtual ~Entity();
	
	void setTexture(const sf::Texture& texture){
		sprite_.setTexture(texture);
		sprite_.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
	}

	void centerOrigin(){
		sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
	}

	void setVelocity(const sf::Vector2f& velocity){
		velocity_ = velocity;
	}

	void setVelocity(const float vx, const float vy){
		velocity_ = sf::Vector2f(vx, vy);
	}

	void adjustMaxVelocity(){
		if (abs(velocity_.x) > maxVelocity_.x)
			maxVelocity_.x = abs(velocity_.x);
		if (abs(velocity_.y) > maxVelocity_.y)
			maxVelocity_.y = abs(velocity_.y);
	}

	void setMaxVelocity(const sf::Vector2f& maxVelocity){
		maxVelocity_ = maxVelocity;
	}

	void setMaxVelocity(const float vx,const float vy){
		maxVelocity_ = sf::Vector2f(vx, vy);
	}

	void setAcceleration(const sf::Vector2f& acceleration){
		acceleration_ = acceleration;
	}

	void setAcceleration(const float ax, const float ay){
		acceleration_ = sf::Vector2f(ax,ay);
	}

	void setAccelerationValues(const sf::Vector2f& accValues){
		accValues_ = accValues;
	}

	void setAccelerationValues(const float xVal, const float yVal){
		accValues_ = sf::Vector2f(xVal,yVal);
	}

	virtual void create(const sf::Texture& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues);
	virtual void create(const sf::Texture& texture, const float vx, const float vy, const float ax, const float ay, const float maxVx, const float maxVy, const float accValueX, const float accValueY);
	virtual void update(const sf::Time& dt);
};