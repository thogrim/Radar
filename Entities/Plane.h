/*
	TODO:
	in setDestination method check if it is possible to reach destination
	change selection sprite to primitive
*/
#pragma once

#include "Entity.h"
#include "Selectable.h"
#include <iostream>

const float PI = 3.14159265f;

class Plane: public Entity, public Selectable{
private:
	/*
		Plane's velocity and acceleration values
		are in polar coordinate system!
	*/
	bool hovered_;
	bool selected_;
	bool hasDestination_;
	sf::Vector2f destination_;

	sf::IntRect hoveredRect_;
	sf::IntRect selectedRect_;
	sf::Sprite selectionSprite_;

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void updateCurrent(const sf::Time& dt);
	float countAngleDifferrence();
public:
	Plane(const sf::Texture& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues);
	Plane(const sf::Texture& texture, const float vx, const float vy, const float ax, const float ay, const float maxVx, const float maxVy, const float accValueX, const float accValueY);
	Plane();
	~Plane();

	void setSelectionTexture(const sf::Texture& texture);
	bool selected() const;
	bool hovered() const;
	bool hover(const sf::Vector2i& mousePos);
	bool select();
	bool unselect();
	void setDestination(const sf::Vector2i& destination);
};