#pragma once

#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"
#include "Entities/Plane.h"
#include <fstream>
#include <regex>
#include <iostream>

class World: public sf::Drawable{
private:
	//sf::RenderWindow& window_;
	ResourceHolder<sf::Texture>& textures_;
	ResourceHolder<sf::Font>& fonts_;
	std::vector<Plane> planes_;
	Plane* selectedPlane;
	Plane* hoveredPlane;
	
	void spawnSlowPlane();
	void spawnFastPlane();
public:
	World(ResourceHolder<sf::Texture>& textures, ResourceHolder<sf::Font>& fonts);
	~World();

	void init(const std::string& filename);
	//void processEvents(const sf::Event& ev);
	bool press();
	void setPlaneDestination(const sf::Vector2i& mousePos);
	void hover(const sf::Vector2i& mousePos);
	void updateDebug();
	void update(const sf::Time& dt);
	//void renderDebug() const;
	//void render() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};