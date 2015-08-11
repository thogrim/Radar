#include "World.h"

const std::string World::SlowPlaneId = "SlowPlane:";
const std::string World::FastPlaneId = "FastPlane:";
const std::string World::MountainId = "Mountain:";
const std::string World::MistId = "Mist:";
const std::string World::BounsId = "Bonus:";
const std::regex World::Position = std::regex("position:([[:d:]]+),([[:d:]]+)");
const std::regex World::Rotation = std::regex("rotation:([[:d:]]+)");
const std::regex World::Velocity = std::regex("velocity:([[:d:]]+),([[:d:]]+)");
const std::regex World::Vertex = std::regex("([[:d:]]+),([[:d:]]+)");
const std::regex World::Time = std::regex("time:([[:d:]]+)");
const std::string World::End = "end";

World::World(ResourceHolder<sf::Texture>& textures, ResourceHolder<sf::Font>& fonts)
	:textures_(textures),
	fonts_(fonts),
	planes_(),
	selectedPlane_(nullptr),
	hoveredPlane_(nullptr),
	timer_(sf::Time::Zero),
	pendingPlanes_(){
}

World::~World(){
	for (Plane* p : planes_){
		delete p;
	}
	while (!pendingPlanes_.empty()){
		delete pendingPlanes_.front().first;
		pendingPlanes_.pop();
	}
}

void World::loadPlaneAttributes(Plane* plane, std::ifstream& file){
	//Plane* plane = new Plane(textures_.get("slowplane"));
	//plane->setVelocity(0.f,20.f);
	//plane->setMaxVelocity(50.f, 40.f);
	//plane->setHitboxRadius(30.f);
	float time = -1.f;
	std::smatch matches;
	std::string line = "";
	std::getline(file, line);
	while (line != End){
		if (std::regex_search(line, matches, Position)){
			std::string xpos = matches[1];
			std::string ypos = matches[2];
			plane->setPosition(std::stof(xpos), std::stof(ypos));
		}
		else if (std::regex_search(line, matches, Rotation)){
			std::string rot = matches[1];
			plane->setRotation(std::stof(rot));
		}
		else if (std::regex_search(line, matches, Time)){
			std::string t = matches[1];
			time = std::stof(t);
		}
		else{
			std::cout << "Error! Unrecognized attribute: " << line << std::endl;
		}
	std::getline(file, line);
	}
	if (time > 0)
		pendingPlanes_.push(std::make_pair(plane, time));
	else
		planes_.push_back(plane);
}

//void World::spawnFastPlane(){
//	Plane plane(textures_.get("fastplane"));
//	plane.setVelocity(0.f, 40.f);
//	plane.setMaxVelocity(100.f, 100.f);
//	plane.setHitboxRadius(30.f);
//	planes_.push_back(plane);
//}

void World::init(const std::string& filename){
	std::ifstream file(filename);
	if (!file.good()){
		std::cout << "could not open file: " << filename << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file, line)){
		if (line == SlowPlaneId){
			Plane* plane = new Plane(textures_.get("slowplane"));
			plane->setVelocity(0.f, 20.f);
			plane->setMaxVelocity(50.f, 40.f);
			plane->setHitboxRadius(32.f);
			loadPlaneAttributes(plane, file);
		}
		else if (line == FastPlaneId){
			Plane* plane = new Plane(textures_.get("fastplane"));
			plane->setVelocity(0.f, 40.f);
			plane->setMaxVelocity(100.f, 100.f);
			plane->setHitboxRadius(35.f);
			loadPlaneAttributes(plane,file);
		}
		else{
			std::cout << "Error! Unrecognized entity: " << line << std::endl;
		}
	}
		
}

bool World::press(){
	if (hoveredPlane_){
		hoveredPlane_->select();
		if (selectedPlane_ && selectedPlane_ != hoveredPlane_)
			selectedPlane_->unselect();
		selectedPlane_ = hoveredPlane_;
		return true;
	}
	else if (!hoveredPlane_ && selectedPlane_){
		selectedPlane_->unselect();
		selectedPlane_ = nullptr;
		return true;
	}
	else
		return false;
}

void World::setPlaneDestination(const sf::Vector2i& mousePos) {
	if (selectedPlane_)
		selectedPlane_->setDestination(mousePos);
}

void World::updateDebug(){

}

void World::hover(const sf::Vector2i& mousePos){
	for (Plane* p : planes_){
		if (p->hover(mousePos)){
			hoveredPlane_ = p;
			break;
		}
		hoveredPlane_ = nullptr;
	}
}

void World::update(const sf::Time& dt){
	for (Plane* p : planes_){
		p->update(dt);
	}

	//update timer and spawn new entities
	timer_ += dt;
	if (!pendingPlanes_.empty()){
		if (timer_.asSeconds() > pendingPlanes_.front().second){
			planes_.push_back(pendingPlanes_.front().first);
			pendingPlanes_.pop();
		}
	}
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	for (const Plane* p : planes_){
		p->draw(target, states);
	}
}