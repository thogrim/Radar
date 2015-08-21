#pragma once

#include "ShapeEntity.h"

class Mist: public ShapeEntity{
public:
	Mist(const sf::Texture& texture, const Vertices& vertices);
	Mist(const sf::Texture& texture);
	~Mist();

	void update(const sf::Time& dt);

	void accept(Visitor& c);
};

