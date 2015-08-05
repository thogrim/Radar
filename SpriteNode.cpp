#include "SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture& texture)
	:SceneNode(),
	sprite_(){
	sprite_.setTexture(texture);
}

SpriteNode::SpriteNode()
	:SceneNode(),
	sprite_(){
}

SpriteNode::~SpriteNode(){
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(sprite_, states);
}

void SpriteNode::updateCurrent(const sf::Time& dt){

}

void SpriteNode::setTexture(const sf::Texture& texture){
	sprite_.setTexture(texture);
}