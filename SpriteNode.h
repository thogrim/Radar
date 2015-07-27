#pragma once

#include "SceneNode.h"

class SpriteNode:public SceneNode{
protected:
	sf::Sprite sprite_;
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	SpriteNode(const sf::Texture& texture);
	SpriteNode();
	~SpriteNode();

	virtual void update(const sf::Time& dt);
	void setTexture(const sf::Texture& texture);
};

