#pragma once

#include "../SceneNode.h"

class Entity: public SceneNode{
private:
	sf::Sprite sprite_;
	sf::Vector2f velocity_;
	//sf::Vector2f acceleration_;

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Entity(sf::Texture& texture, float vx, float vy);
	Entity(sf::Texture& texture, sf::Vector2f velocity);
	Entity(sf::Texture& texture);
	virtual ~Entity();

	//void createButton(const sf::Texture& texture, std::function<void()> action){
	//	button_.setTexture(texture);
	//	button_.setAction(action);
	//}

	void update(const sf::Time& dt, const sf::Vector2i& mousePos);
};