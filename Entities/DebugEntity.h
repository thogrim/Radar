#pragma once

#include "Plane.h"

class DebugEntity: public Plane{
public:
	DebugEntity(const sf::Texture& texture);
	~DebugEntity();

	void setDestination(const sf::Vector2i& destination);

	void update(const sf::Time& dt);
};

