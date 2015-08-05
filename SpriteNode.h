#pragma once

#include "SceneNode.h"

class SpriteNode:public SceneNode{
protected:
	sf::Sprite sprite_;

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void updateCurrent(const sf::Time& dt);
public:
	SpriteNode(const sf::Texture& texture);
	SpriteNode();
	~SpriteNode();

	void setTexture(const sf::Texture& texture);
};

