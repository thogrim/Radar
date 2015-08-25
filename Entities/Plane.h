/*
	TODO:
	1.in setDestination method check if it is possible to reach destination?
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
	sf::Vector2f tempDestination_;
	sf::CircleShape selection_;
	float hitboxRadius_;
	bool visible_;
	sf::Vector2f endDestination_;
	bool reachedDestination_;
	float collectedPoints_;
	sf::Time lifetime_;
	sf::Time timePassed_;

	float countAngleDifferrence();
	void drawFuel(sf::RenderTarget& target) const;
public:
	Plane(const sf::Vector2f& velocity, float hitboxRadius, const sf::Texture& texture);
	Plane(float vx, float vy, float hitboxRadius, const sf::Texture& texture);
	Plane(const sf::Texture& texture);
	~Plane();

	void setLifetime(float lifetime);
	void setHitboxRadius(float radius);
	const float getHitboxRadius() const;
	void setVisibility(bool visible);
	virtual void setTempDestination(const sf::Vector2i& destination);
	void setEndDestination(float x, float y);
	bool reachedDestination() const;
	void collectPoints(float points);
	float takePoints();

	//Selectable
	bool selected() const;
	bool hovered() const;
	bool hover(const sf::Vector2i& mousePos);
	bool select();
	void unselect();

	//
	void update(const sf::Time& dt);
	void drawTempDestination(sf::RenderTarget& target) const;
	void drawEndDestination(sf::RenderTarget& target) const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void accept(Visitor& c);
};