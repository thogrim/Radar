#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <algorithm>
#include <cassert>

class SceneNode: public sf::Drawable, public sf::Transformable{
private:
	typedef std::unique_ptr<SceneNode> ScenePtr;
	SceneNode* parent_;
	std::vector<ScenePtr> children_;

	//for test purposes
	sf::Sprite sprite_;

public:
	SceneNode();
	~SceneNode();
	
	void attachChild(ScenePtr child);
	ScenePtr detachChild(const SceneNode& child);
	virtual void update(const sf::Time& dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const; //virtual?
	//virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Transform getWorldTransform();
	sf::Vector2f getWorldPosition();

	//test
	void setTexture(const sf::Texture& texture){
		sprite_.setTexture(texture);
	}
};