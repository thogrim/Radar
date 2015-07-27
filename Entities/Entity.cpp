#include "Entity.h"

Entity::Entity(sf::Texture& texture, float vx, float vy)
	:SceneNode(),
	sprite_(),
	velocity_(vx,vy){
	sprite_.setTexture(texture);
	//testing button
}

Entity::Entity(sf::Texture& texture, sf::Vector2f velocity)
	:SceneNode(),
	sprite_(),
	velocity_(velocity){
	sprite_.setTexture(texture);
}

Entity::Entity(sf::Texture& texture)
	:Entity(texture,0,0){
}

//Entity::Entity() 
//	:SceneNode(),
//	sprite_(),
//	velocity_(),
//	button_(),
//	pressed_(false){
//}

Entity::~Entity(){
}

void Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(sprite_, states);
}

void Entity::update(const sf::Time& dt, const sf::Vector2i& mousePos){
}