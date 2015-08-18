#pragma once

#include "Entity.h"

class SpriteEntity: public Entity{
protected:
	sf::Sprite sprite_;
public:
	SpriteEntity(const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues);
	SpriteEntity(float vx, float vy, float ax, float ay, float maxVx, float maxVy, float accValueX, float accValueY);
	SpriteEntity();
	virtual ~SpriteEntity();

	void setTexture(const sf::Texture& texture);
	void centerOrigin();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//virtual void accept(Visitor& c) = 0;
};

