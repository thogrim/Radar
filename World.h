#pragma once

#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"
#include "Entities/Plane.h"
#include "Entities/Mountain.h"
#include "Entities/Mist.h"
#include "Entities/Bonus.h"
#include "Entities/DebugEntity.h"
#include "Collider.h"
#include <fstream>
#include <regex>
#include <iostream>
#include <queue>
#include <list>

class World: public sf::Drawable{
private:
	//identifiers for reading files
	static const std::string SLOW_PLANE_ID_;
	static const std::string FAST_PLANE_ID_;
	static const std::string SUPER_FAST_PLANE_ID_;
	static const std::string DEBUG_ENTITY_ID_;
	static const std::string MOUNTAIN_ID_;
	static const std::string MIST_ID_;
	static const std::string BONUS_ID_;
	static const std::regex POSITION_;
	static const std::regex ROTATION_;
	static const std::regex VELOCITY_;
	static const std::regex VERTEX_;
	static const std::regex SCORE_;
	static const std::regex LIFETIME_;
	static const std::regex TIME_;
	static const std::string END_;
	//identfiers end
private:
	ResourceHolder<sf::Texture>& textures_;
	ResourceHolder<sf::Font>& fonts_;
	std::list<Plane*> planes_;
	std::list<Entity*> entities_;
	Plane* selectedPlane_;
	Plane* hoveredPlane_;
	bool drawDestinations;
		
	sf::Time timer_;
	std::queue<std::pair<Plane*,float>> pendingPlanes_;
	std::queue<std::pair<Entity*,float>> pendingEntities_;

	void loadPlaneAttributes(Plane* plane, std::ifstream& file);
	void loadShapeAttributes(ShapeEntity* shapeEntity, std::ifstream& file);
	void loadBonusAttributes(Bonus* bonus, std::ifstream& file);

	void checkCollisions();
	void drawPlanesDestinations(sf::RenderTarget& target) const;
public:
	World(ResourceHolder<sf::Texture>& textures, ResourceHolder<sf::Font>& fonts);
	~World();

	sf::Time getTimer() const;

	void init(const std::string& filename);
	bool press();
	void setPlaneDestination(const sf::Vector2i& mousePos);
	void setDrawingDestinations();
	void hover(const sf::Vector2i& mousePos);
	void update(const sf::Time& dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};