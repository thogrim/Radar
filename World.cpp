#include "World.h"

World::World(sf::RenderWindow& window, ResourceHolder<sf::Texture>& textures, ResourceHolder<sf::Font>& fonts)
	:window_(window),
	textures_(textures),
	fonts_(fonts){
}

World::~World(){
}

void World::init(){

}

void World::processEvents(const sf::Event& ev){

}

void World::updateDebug(){

}

void World::update(const sf::Time& dt){

}

void World::renderDebug() const{

}

void World::render() const{

}