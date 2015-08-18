#pragma once

#include "ShapeEntity.h"

class Mountain: public ShapeEntity{
public:
	//Mountain(const ResourceHolder<sf::Texture>& textures,const Vertices& vertices);
	Mountain(const Vertices& vertices);
	Mountain();
	~Mountain();

	void update(const sf::Time& dt);

	void accept(Visitor& c);
};