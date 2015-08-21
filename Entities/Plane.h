/*
	TODO:
	1.in setDestination method check if it is possible to reach destination
*/
#pragma once

#include "SpriteEntity.h"
#include "Selectable.h"
#include "../ResourceHolder.h"

const float PI = 3.14159265f;

class Plane: public SpriteEntity, public Selectable{
protected:
	/*
		Plane's velocity and acceleration values
		are in polar coordinate system!
	*/
	bool hovered_;
	bool selected_;
	bool hasDestination_;
	sf::Vector2f destination_;
	sf::CircleShape selection_;
	float hitboxRadius_;

	float countAngleDifferrence();
public:
	Plane(const sf::Vector2f& velocity, float hitboxRadius, const sf::Texture& texture);
	Plane(float vx, float vy, float hitboxRadius, const sf::Texture& texture);
	Plane(const sf::Texture& texture);
	~Plane();

	void setHitboxRadius(float radius);
	const float getHitboxRadius() const;

	//Selectable
	bool selected() const;
	bool hovered() const;
	bool hover(const sf::Vector2i& mousePos);
	bool select();
	void unselect();

	//
	virtual void setDestination(const sf::Vector2i& destination);
	void update(const sf::Time& dt);
	void drawDestination(sf::RenderTarget& target/*, sf::RenderStates states*/) const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void accept(Visitor& c);
};