#pragma once

#include "ShapeEntity.h"

class Mist: public ShapeEntity{
public:
	Mist(const sf::Texture& texture, const Vertices& vertices);
	Mist(const sf::Texture& texture);
	~Mist();

	void accept(Visitor& c);
};

