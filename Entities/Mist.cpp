#include "Mist.h"

Mist::Mist(const sf::Texture& texture, const Vertices& vertices)
	:ShapeEntity(vertices){
	setTexture(texture);
}

Mist::Mist(const sf::Texture& texture)
	:Mist(texture,Vertices()){
}

Mist::~Mist(){
}

void Mist::update(const sf::Time& dt){
	move(velocity_*dt.asSeconds());
}


void Mist::accept(Visitor& c){
	c.visit(*this);
}