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

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(const sf::Time& dt);
public:
	SceneNode();
	//SceneNode(const SceneNode& node);
	virtual ~SceneNode();
	

	void attachChild(ScenePtr child);
	ScenePtr detachChild(const SceneNode& child);
	void update(const sf::Time& dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Transform getWorldTransform();
	sf::Vector2f getWorldPosition();
};