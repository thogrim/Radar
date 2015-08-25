#pragma once

#include "Plane.h"

class DebugEntity: public Plane{
public:
	DebugEntity(const sf::Texture& texture);
	~DebugEntity();

	void setTempDestination(const sf::Vector2i& destination);

	void update(const sf::Time& dt);
};