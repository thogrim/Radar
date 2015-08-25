#include "World.h"

const std::string World::SLOW_PLANE_ID_ = "SlowPlane:";
const std::string World::FAST_PLANE_ID_ = "FastPlane:";
const std::string World::SUPER_FAST_PLANE_ID_ = "SuperFastPlane:";
const std::string World::DEBUG_ENTITY_ID_ = "DebugEntity:";
const std::string World::MOUNTAIN_ID_ = "Mountain:";
const std::string World::MIST_ID_ = "Mist:";
const std::string World::BONUS_ID_ = "Bonus:";
const std::regex World::POSITION_ = std::regex("position:(-?[[:d:]]+),(-?[[:d:]]+)");
const std::regex World::ROTATION_ = std::regex("rotation:(-?[[:d:]]+)");
const std::regex World::VELOCITY_ = std::regex("velocity:(-?[[:d:]]+),(-?[[:d:]]+)");
const std::regex World::VERTEX_ = std::regex("vertex:(-?[[:d:]]+),(-?[[:d:]]+)");
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
	drawDestinations(false),
	score_(0.f),
	HUDtext_(),
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
			vertices.push_back(sf::Vector2f(std::stof(x), std::stof(y)));
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
	if (vertices.size() > 2){
		if (vertices[0].x*vertices[1].y - vertices[1].x*vertices[0].y > 0)
			std::reverse(vertices.begin(), vertices.end());
		shapeEntity->setVertices(vertices);
		if (time > 0)
			pendingEntities_.push(std::make_pair(shapeEntity, time));
		else
			entities_.push_back(shapeEntity);
	}
	else
		std::cout << "Error! Shape contains less than 3 vertices and it will not be put into the game\n";
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
		pendingEntities_.push(std::make_pair(bonus, time));
	else
		entities_.push_back(bonus);
}

void World::init(const std::string& filename){
	HUDtext_.setFont(fonts_.get("calibri"));
	HUDtext_.setCharacterSize(20);
	HUDtext_.setPosition(600, 0);
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
			plane->setEndDestination(300.f, 200.f);
			loadPlaneAttributes(plane, file);
		}
		else if (line == FAST_PLANE_ID_){
			//std::unique_ptr<Plane> plane(new Plane(textures_.get("fastplane")));
			Plane* plane = new Plane(textures_.get("fastplane"));
			plane->setVelocity(0.f, 40.f);
			plane->setMaxVelocity(100.f, 100.f);
			plane->setHitboxRadius(35.f);
			plane->setEndDestination(200.f, 300.f);
			plane->setLifetime(25.f);
			loadPlaneAttributes(plane,file);
		}
		else if (line == SUPER_FAST_PLANE_ID_){
			//std::unique_ptr<Plane> plane(new Plane(textures_.get("fastplane")));
			Plane* plane = new Plane(textures_.get("superfastplane"));
			plane->setVelocity(0.f, 40.f);
			plane->setMaxVelocity(200.f, 300.f);
			plane->setHitboxRadius(35.f);
			loadPlaneAttributes(plane, file);
		}
		else if (line == DEBUG_ENTITY_ID_){
			Plane* debug = new DebugEntity(textures_.get("debug"));
			debug->setVelocity(0.f, 0.f);
			debug->setMaxVelocity(100.f, 0.f);
			debug->setHitboxRadius(15.f);
			loadPlaneAttributes(debug, file);
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
		selectedPlane_->setTempDestination(mousePos);
}

void World::setDrawingDestinations(){
	drawDestinations = !drawDestinations;
}

void World::hover(const sf::Vector2i& mousePos){
	for (auto& p : planes_){
		if (p->hover(mousePos)){
			hoveredPlane_ = p;
			break;
		}
		hoveredPlane_ = nullptr;
	}
}

void World::checkCollisions(){
	for (Plane* p : planes_){
		Collider c(*p);
		for (Entity* e : entities_){
			e->accept(c);
		}
	}
}

void World::update(const sf::Time& dt){
	//updating planes
	auto plane = planes_.begin();
	while (plane != planes_.end()){
		if ((*plane)->toDestroy()){
			//destroy plane
			if (*plane == selectedPlane_)
				selectedPlane_ = nullptr;
			delete *plane;
			plane = planes_.erase(plane);
		}
		else if((*plane)->reachedDestination()){
			//remove plane when it reached its destination
			score_ += (*plane)->takePoints();
			if (*plane == selectedPlane_)
				selectedPlane_ = nullptr;
			delete *plane;
			plane = planes_.erase(plane);
		}
		else{
			//update plane and take points
			score_ +=(*plane)->takePoints();
			(*plane)->update(dt);
			++plane;
		}
	}

	//updating entities
	auto entity = entities_.begin();
	while (entity != entities_.end()){
		if ((*entity)->toDestroy()){
			//destroy entity
			delete *entity;
			entity = entities_.erase(entity);
		}
		else{
			//update entity
			(*entity)->update(dt);
			++entity;
		}
	}

	//check collisions
	checkCollisions();

	//update timer and spawn new entities
	timer_ += dt;
	if (!pendingPlanes_.empty()){
		if (timer_.asSeconds() > pendingPlanes_.front().second){
			planes_.push_back(pendingPlanes_.front().first);
			pendingPlanes_.pop();
		}
	}
	if (!pendingEntities_.empty()){
		if (timer_.asSeconds() > pendingEntities_.front().second){
			entities_.push_back(pendingEntities_.front().first);
			pendingEntities_.pop();
		}
	}

	//update HUD
	HUDtext_.setString("score: " + std::to_string(score_));
}

void World::drawPlanesDestinations(sf::RenderTarget& target) const{
	for (const Plane* p : planes_){
		p->drawTempDestination(target);
	}
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	for (const Entity* e : entities_){
		e->draw(target, states);
	}
	if (drawDestinations)
		drawPlanesDestinations(target);
	for (const Plane* p : planes_){
		p->draw(target, states);
	}

	target.draw(HUDtext_);
}