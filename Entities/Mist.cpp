#include "Mist.h"

Mist::Mist(const sf::Texture& texture, const Vertices& vertices)
	:ShapeEntity(vertices){
	setTexture(texture);
	//shape_.setOutlineThickness(-5);
	//shape_.setOutlineColor(sf::Color(127, 127, 127));
}

Mist::Mist(const sf::Texture& texture)
	:Mist(texture,Vertices()){
	//setTexture(texture);
	//shape_.setOutlineThickness(-5);
	//shape_.setOutlineColor(sf::Color(127, 127, 127));
}

Mist::~Mist(){
}

void Mist::accept(Visitor& c){
	c.visit(*this);
}