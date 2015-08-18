#include "World.h"

const std::string World::SLOW_PLANE_ID_ = "SlowPlane:";
const std::string World::FAST_PLANE_ID_ = "FastPlane:";
const std::string World::MOUNTAIN_ID_ = "Mountain:";
const std::string World::MIST_ID_ = "Mist:";
const std::string World::BONUS_ID_ = "Bonus:";
const std::regex World::POSITION_ = std::regex("position:([[:d:]]+),([[:d:]]+)");
const std::regex World::ROTATION_ = std::regex("rotation:([[:d:]]+)");
const std::regex World::VELOCITY_ = std::regex("velocity:([[:d:]]+),([[:d:]]+)");
const std::regex World::VERTEX_ = std::regex("([[:d:]]+),([[:d:]]+)");
const std::regex World::SCORE_ = std::regex("score:([[:d:]]+)");
const std::regex World::LIFETIME_ = std::regex("lifetime:([[:d:]]+)");
const std::regex World::TIME_ = std::regex("time:([[:d:]]+)");
const std::string World::END_ = "end";

World::World(ResourceHolder<sf::Texture>& textures, ResourceHolder<sf::Font>& fonts)
	:textures_(textures),
	fonts_(fonts),
	planes_(),
	entities_(),
	selectedPlane_(nullptr),
	hoveredPlane_(nullptr),
	timer_(sf::Time::Zero),
	pendingPlanes_(),
	pendingEntities_(){
}

World::~World(){
	for (Plane* p : planes_){
		delete p;
	}
	for (Entity* e : entities_){
		delete e;
	}
	while (!pendingPlanes_.empty()){
		delete pendingPlanes_.front().first;
		pendingPlanes_.pop();
	}
	while (!pendingEntities_.empty()){
		delete pendingEntities_.front().first;
		pendingEntities_.pop();
	}
}

void World::loadPlaneAttributes(Plane* plane, std::ifstream& file){
	float time = -1.f;
	std::smatch matches;
	std::string line = "";
	std::getline(file, line);
	while (line != END_){
		if (std::regex_search(line, matches, POSITION_)){
			std::string xpos = matches[1];
			std::string ypos = matches[2];
			plane->setPosition(std::stof(xpos), std::stof(ypos));
		}
		else if (std::regex_search(line, matches, ROTATION_)){
			std::string rot = matches[1];
			plane->setRotation(std::stof(rot));
		}
		else if (std::regex_search(line, matches, TIME_)){
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

void World::loadShapeAttributes(ShapeEntity* shapeEntity, std::ifstream& file){
	float time = -1.f;
	std::smatch matches;
	std::string line = "";
	std::getline(file, line);
	ShapeEntity::Vertices vertices;
	while (line != END_){
		if (std::regex_search(line, matches, VERTEX_)){
			std::string x = matches[1];
			std::string y = matches[2];
			vertices.push_back(std::make_pair(std::stof(x), std::stof(y)));
		}
		else if (std::regex_search(line, matches, VELOCITY_)){
			std::string vx = matches[1];
			std::string vy = matches[2];
			shapeEntity->setVelocity(std::stof(vx), std::stof(vy));
			shapeEntity->adjustMaxVelocity();
		}
		else if (std::regex_search(line, matches, TIME_)){
			std::string t = matches[1];
			time = std::stof(t);
		}
		else{
			std::cout << "Error! Unrecognized attribute: " << line << std::endl;
		}
		std::getline(file, line);
	}
	shapeEntity->setVertices(vertices);
	if (time > 0)
		pendingEntities_.push(std::make_pair(std::move(shapeEntity), time));
	else
		entities_.push_back(shapeEntity);
}

void World::loadBonusAttributes(Bonus* bonus, std::ifstream& file){
	float time = -1.f;
	std::smatch matches;
	std::string line = "";
	std::getline(file, line);
	while (line != END_){
		if (std::regex_search(line, matches, POSITION_)){
			std::string xpos = matches[1];
			std::string ypos = matches[2];
			bonus->setPosition(std::stof(xpos), std::stof(ypos));
		}
		else if (std::regex_search(line, matches, SCORE_)){
			std::string score = matches[1];
			bonus->setScore(std::stoi(score));
		}
		else if (std::regex_search(line, matches, LIFETIME_)){
			std::string lifetime = matches[1];
			bonus->setLifetime(std::stoi(lifetime));
		}
		else if (std::regex_search(line, matches, TIME_)){
			std::string t = matches[1];
			time = std::stof(t);
		}
		else{
			std::cout << "Error! Unrecognized attribute: " << line << std::endl;
		}
		std::getline(file, line);
	}
	if (time > 0)
		pendingEntities_.push(std::make_pair(std::move(bonus), time));
	else
		entities_.push_back(bonus);
}

void World::init(const std::string& filename){
	std::ifstream file(filename);
	if (!file.good()){
		std::cout << "could not open file: " << filename << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file, line)){
		if (line == SLOW_PLANE_ID_){
			//std::unique_ptr<Plane> plane(new Plane(textures_.get("slowplane")));
			Plane* plane = new Plane(textures_.get("slowplane"));
			plane->setVelocity(0.f, 20.f);
			plane->setMaxVelocity(50.f, 40.f);
			plane->setHitboxRadius(32.f);
			loadPlaneAttributes(plane, file);
		}
		else if (line == FAST_PLANE_ID_){
			//std::unique_ptr<Plane> plane(new Plane(textures_.get("fastplane")));
			Plane* plane = new Plane(textures_.get("fastplane"));
			plane->setVelocity(0.f, 40.f);
			plane->setMaxVelocity(100.f, 100.f);
			plane->setHitboxRadius(35.f);
			loadPlaneAttributes(plane,file);
		}
		else if (line == MOUNTAIN_ID_){
			//std::unique_ptr<ShapeEntity> mountain(new Mountain());
			Mountain* mountain = new Mountain();
			loadShapeAttributes(mountain, file);
		}
		else if (line == MIST_ID_){
			//std::unique_ptr<ShapeEntity> mist(new Mist(textures_.get("mist")));
			Mist* mist = new Mist(textures_.get("mist"));
			loadShapeAttributes(mist, file);
		}
		else if (line == BONUS_ID_){
			//std::unique_ptr<Bonus> bonus(new Bonus(textures_.get("bonus")));
			Bonus* bonus = new Bonus(textures_.get("bonus"),fonts_.get("calibri"));
			loadBonusAttributes(bonus, file);
		}
		else{
			std::cout << "Error! Unrecognized entity: " << line << std::endl;
		}
	}
		
}

sf::Time World::getTimer() const{
	return timer_;
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

//void World::updateDebug(){
//
//}

void World::hover(const sf::Vector2i& mousePos){
	for (auto& p : planes_){
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
	for (Entity* e : entities_){
		e->update(dt);
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
	for (const Entity* e : entities_){
		e->draw(target, states);
	}
}