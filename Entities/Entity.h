#pragma once

#include "../SceneNode.h"

class Entity: public SceneNode{
private:
	sf::Sprite sprite_;
	sf::Vector2f velocity_;

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Entity(sf::Texture& texture, float vx, float vy);
	Entity(sf::Texture& texture, sf::Vector2f velocity);
	Entity(sf::Texture& texture);
	~Entity();

	void update(const sf::Time& dt);
};