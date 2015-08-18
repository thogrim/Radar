#include "ShapeEntity.h"

//ShapeEntity::ShapeEntity(const ResourceHolder<sf::Texture>& textures, const Vertices& vertices)
//	:shape_(),
//	bounds_(){
//	shape_.setPointCount(vertices.size());
//	int i = 0;
//	for (auto& v : vertices){
//		shape_.setPoint(i, sf::Vector2f(v.first, v.second));
//		++i;
//	}
//	adjustBounds();
//
//}

ShapeEntity::ShapeEntity(const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues, const Vertices& vertices)
	:Entity(velocity,acceleration,maxVelocity,accValues),
	shape_(),
	bounds_(){
	setVertices(vertices);
}

ShapeEntity::ShapeEntity(float vx, float vy, float ax, float ay, float maxVx, float maxVy, float accValueX, float accValueY, const Vertices& vertices)
	:ShapeEntity(sf::Vector2f(vx, vy), sf::Vector2f(ax, ay), sf::Vector2f(maxVx, maxVy), sf::Vector2f(accValueX, accValueY),vertices){
}

ShapeEntity::ShapeEntity(const Vertices& vertices)
	: ShapeEntity(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, vertices){
}

ShapeEntity::ShapeEntity()
	: Entity(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f),
	shape_(),
	bounds_(){
}

ShapeEntity::~ShapeEntity(){
}

void ShapeEntity::adjustBounds(){
	float xmin = shape_.getPoint(0).x;
	float ymin = shape_.getPoint(0).y;
	float xmax = shape_.getPoint(0).x;
	float ymax = shape_.getPoint(0).y;
	for (int i = 1; i < shape_.getPointCount(); ++i){
		sf::Vector2f point = shape_.getPoint(i);
		if (point.x < xmin)
			xmin = point.x;
		else if (point.x > xmax)
			xmax = point.x;
		if (point.y < ymin)
			ymin = point.y;
		else if (point.y > ymax)
			ymax = point.y;
	}
	bounds_ = sf::FloatRect(xmin, ymin, xmax - xmin, ymax - ymin);
}

void ShapeEntity::setTexture(const sf::Texture& texture){
	shape_.setTexture(&texture,true);
}

void ShapeEntity::setVertices(const Vertices& vertices){
	shape_.setPointCount(vertices.size());
	int i = 0;
	for (auto& v : vertices){
		shape_.setPoint(i, sf::Vector2f(v.first, v.second));
		++i;
	}
	adjustBounds();
	shape_.setTextureRect(static_cast<sf::IntRect>(bounds_));
}

void ShapeEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	target.draw(shape_, states);
}

//void ShapeEntity::update(const sf::Time& dt){
//	//do nothing
//}