#pragma once

#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"
#include "Entities/Plane.h"
#include "Entities/Mountain.h"
#include <fstream>
#include <regex>
#include <iostream>
#include <queue>

class World: public sf::Drawable{
private:
	//identifiers for reading files
	static const std::string SlowPlaneId;
	static const std::string FastPlaneId;
	static const std::string MountainId;
	static const std::string MistId;
	static const std::string BounsId;
	static const std::regex Position;
	static const std::regex Rotation;
	static const std::regex Velocity;
	static const std::regex Vertex;
	static const std::regex Time;
	static const std::string End;
	//identfiers end
private:
	//sf::RenderWindow& window_;
	ResourceHolder<sf::Texture>& textures_;
	ResourceHolder<sf::Font>& fonts_;
	std::vector<Plane*> planes_;
	//std::vector<Mountain> mountains_;
	//std::vector<Mist> mists_;
	//std::vector<Bonus> bonuses_;
	//
	//std::vector<Entity*> entities_;
	Plane* selectedPlane_;
	Plane* hoveredPlane_;
	
	sf::Time timer_;
	std::queue<std::pair<Plane*,float>> pendingPlanes_;
	//std::queue<std::pair<Entity*,sf::Time>> pendingEntities_;

	void loadPlaneAttributes(Plane* plane, std::ifstream& file);

	//void collide(Plane&, Entity&);
public:
	World(ResourceHolder<sf::Texture>& textures, ResourceHolder<sf::Font>& fonts);
	~World();

	void init(const std::string& filename);
	bool press();
	void setPlaneDestination(const sf::Vector2i& mousePos);
	void hover(const sf::Vector2i& mousePos);
	void updateDebug();
	void update(const sf::Time& dt);
	//void renderDebug() const;
	//void render() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};