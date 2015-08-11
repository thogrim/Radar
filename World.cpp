#include "World.h"

World::World(ResourceHolder<sf::Texture>& textures, ResourceHolder<sf::Font>& fonts)
	:textures_(textures),
	fonts_(fonts),
	planes_(),
	selectedPlane(nullptr),
	hoveredPlane(nullptr){
}

World::~World(){
}

void World::spawnSlowPlane(){
	Plane plane(textures_.get("slowplane"));
	plane.setVelocity(0.f,20.f);
	plane.setMaxVelocity(50.f, 40.f);
	plane.setHitboxRadius(30.f);
	planes_.push_back(plane);
}

void World::spawnFastPlane(){
	Plane plane(textures_.get("fastplane"));
	plane.setVelocity(0.f, 40.f);
	plane.setMaxVelocity(100.f, 100.f);
	plane.setHitboxRadius(30.f);
	planes_.push_back(plane);
}

void World::init(const std::string& filename){
	std::ifstream file(filename);
	if (!file.good()){
		std::cout << "could not open file: " << filename << std::endl;
		return;
	}
	std::string line;
	std::smatch matches;
	std::regex slowPlaneId("\\[SlowPlane\\]");
	std::regex fastPlaneId("\\[FastPlane\\]");
	std::regex pos("position:([[:d:]]+),([[:d:]]+)");
	std::regex rot("rotation:([[:d:]]+)");
	std::regex end("\\[end\\]");
	while (std::getline(file, line)){
		if (std::regex_match(line, slowPlaneId)){
			spawnSlowPlane();
			std::getline(file, line);
			while (!regex_match(line, end)){
				if (std::regex_search(line, matches, pos)){
					std::string xpos(matches[1]);
					std::string ypos(matches[2]);
					planes_.back().setPosition(std::stof(xpos), std::stof(ypos));
					
				}
				else if (std::regex_search(line, matches, rot)){
					std::string rotation(matches[1]);
					planes_.back().setRotation(std::stof(rotation));
				}
				else{
					std::cout << "unknown attribute: " << line << std::endl;
				}
				std::getline(file, line);
			}
		}
		else if (std::regex_match(line, fastPlaneId)){
			spawnFastPlane();
			std::getline(file, line);
			while (!regex_match(line, end)){
				if (std::regex_search(line, matches, pos)){
					std::string xpos(matches[1]);
					std::string ypos(matches[2]);
					planes_.back().setPosition(std::stof(xpos), std::stof(ypos));

				}
				else if (std::regex_search(line, matches, rot)){
					std::string rotation(matches[1]);
					planes_.back().setRotation(std::stof(rotation));
				}
				else{
					std::cout << "unknown attribute: " << line << std::endl;
				}
				std::getline(file, line);
			}
		}
		else{
			std::cout << "unknown entity: " << line << std::endl;
		}
	}
}

bool World::press(){
	if (hoveredPlane){
		hoveredPlane->select();
		if (selectedPlane && selectedPlane != hoveredPlane)
			selectedPlane->unselect();
		selectedPlane = hoveredPlane;
		return true;
	}
	else if (!hoveredPlane && selectedPlane){
		selectedPlane->unselect();
		selectedPlane = nullptr;
		return true;
	}
	else
		return false;
}

void World::setPlaneDestination(const sf::Vector2i& mousePos) {
	if (selectedPlane)
		selectedPlane->setDestination(mousePos);
}

void World::updateDebug(){

}

void World::hover(const sf::Vector2i& mousePos){
	for (Plane& p : planes_){
		if (p.hover(mousePos)){
			hoveredPlane = &p;
			break;
		}
		hoveredPlane = nullptr;
	}
}

void World::update(const sf::Time& dt){
	for (Plane& p : planes_){
		p.update(dt);
	}
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	for (const Plane& p : planes_){
		p.draw(target, states);
	}
}