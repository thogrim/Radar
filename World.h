#pragma once

#include "ResourceHolder.h"
#include "SFML/Graphics.hpp"

class World{
private:
	sf::RenderWindow& window_;
	ResourceHolder<sf::Texture>& textures_;
	ResourceHolder<sf::Font>& fonts_;
	SceneNode scene_;
public:
	World(sf::RenderWindow& window, ResourceHolder<sf::Texture>& textures, ResourceHolder<sf::Font>& fonts);
	~World();

	void init();
	void processEvents(const sf::Event& ev);
	void updateDebug();
	void update(const sf::Time& dt);
	void renderDebug() const;
	void render() const;
};