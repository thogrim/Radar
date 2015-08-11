#include "Mountain.h"

//Mountain::Mountain(const ResourceHolder<sf::Texture>& textures, const Vertices& vertices)
//	:ShapeEntity(vertices){
//	//set Texture here
//	shape_.setTexture(textures.get());
//}

Mountain::Mountain(const Vertices& vertices)
	:ShapeEntity(vertices){
	shape_.setFillColor(sf::Color(195, 195, 195));
	shape_.setOutlineThickness(-5);
	shape_.setOutlineColor(sf::Color(127, 127, 127));
}

Mountain::Mountain()
	:ShapeEntity(){
	shape_.setFillColor(sf::Color(195, 195, 195));
	shape_.setOutlineThickness(-5);
	shape_.setOutlineColor(sf::Color(127, 127, 127));
}

Mountain::~Mountain(){
}

void Mountain::update(const sf::Time& dt){
	//do nothing
}