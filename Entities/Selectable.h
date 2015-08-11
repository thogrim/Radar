#pragma once

#include <SFML/Graphics.hpp>

class Selectable{
public:
	virtual bool hover(const sf::Vector2i& mousePos) = 0;
	virtual bool select() = 0;
	virtual void unselect() = 0;
	virtual bool selected() const = 0;
	virtual bool hovered() const = 0;
};