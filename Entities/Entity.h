#pragma once

#include <SFML/Graphics.hpp>
#include "../Visitor.h"
//#include "../ResourceHolder.h"

//class Visitor;

class Entity: public sf::Drawable, public sf::Transformable{
protected:
	//sf::Sprite sprite_;
	sf::Vector2f velocity_;		//current velocity
	sf::Vector2f acceleration_;	//current acceleration
	sf::Vector2f maxVelocity_;	//max velocity
	sf::Vector2f accValues_;	//values at which entity accelerates

	//virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	//virtual void updateCurrent(const sf::Time& dt);
	void adjustVelocity(); //adjusts velocity so it does not exceed max velocity
public:
	Entity(/*const ResourceHolder<sf::Texture>& texture, */const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues);
	Entity(/*const sf::Texture& texture,*/ float vx, float vy, float ax, float ay, float maxVx, float maxVy, float accValueX, float accValueY);
	//Entity(const sf::Texture& texture);
	//Entity(const Entity& e);
	Entity();
	virtual ~Entity();
	
	//void setTexture(const sf::Texture& texture);
	//void centerOrigin();
	void setVelocity(const sf::Vector2f& velocity);
	void setVelocity(float vx, float vy);
	void adjustMaxVelocity();
	void setMaxVelocity(const sf::Vector2f& maxVelocity);
	void setMaxVelocity(float vx, float vy);
	void setAcceleration(const sf::Vector2f& acceleration);
	void setAcceleration(float ax, float ay);
	void setAccelerationValues(const sf::Vector2f& accValues);
	void setAccelerationValues(float xVal, float yVal);

	//virtual void create(const sf::Texture& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues);
	//virtual void create(const sf::Texture& texture, float vx, float vy, float ax, float ay, float maxVx, float maxVy, float accValueX, float accValueY);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const=0;
	virtual void update(const sf::Time& dt);

	virtual void accept(Visitor& c) = 0;
};