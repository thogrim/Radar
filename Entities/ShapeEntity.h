#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "../ResourceHolder.h"

class ShapeEntity: public Entity{
protected:
	sf::ConvexShape shape_;
	sf::FloatRect bounds_;

	void adjustBounds();//adjusts bounds to shape
public:
	typedef std::vector<sf::Vector2f> Vertices;

	ShapeEntity(const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues, const Vertices& vertices);
	ShapeEntity(float vx, float vy, float ax, float ay, float maxVx, float maxVy, float accValueX, float accValueY, const Vertices& vertices);
	ShapeEntity(const Vertices& vertices);
	ShapeEntity();
	virtual ~ShapeEntity();

	void setTexture(const sf::Texture& texture);
	void setVertices(const Vertices& vertices);

	const sf::FloatRect& getBounds() const;
	const sf::ConvexShape& getShape() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//virtual void update(const sf::Time& dt);

	//virtual void accept(Visitor& c) = 0;
};