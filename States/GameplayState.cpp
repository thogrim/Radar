#include "GameplayState.h"

GameplayState::GameplayState(ChangeableContainer<State>* stateManager, sf::RenderWindow& window)
	:State(stateManager,window),
	menuButton_(),
	mountain_(),
	world_(textures_,fonts_){
	std::vector<std::pair<float, float>> vertices;
	vertices.push_back(std::make_pair<float,float>(50,50));
	vertices.push_back(std::make_pair<float, float>(500, 60));
	vertices.push_back(std::make_pair<float, float>(570, 380));
	vertices.push_back(std::make_pair<float, float>(100, 450));
	mountain_.setVertices(vertices);
}

GameplayState::GameplayState(const Context& context)
	:GameplayState(context.stateManager_,context.window_){
}

GameplayState::~GameplayState(){
}

void GameplayState::init(){
	try{
		textures_.load("button", "res/img/button.png");
		//textures_.load("plane", "res/img/plane.png");
		//textures_.load("selection", "res/img/selection.png");
		textures_.load("slowplane", "res/img/slowplane.png");
		textures_.load("fastplane", "res/img/fastplane.png");
	}
	catch (std::runtime_error& e){
		std::cout << e.what() << std::endl;
	}
	menuButton_.setTexture(textures_.get("button"));
	menuButton_.setPosition(300, 200);
	menuButton_.setAction([this](){
		context_.stateManager_->change(new MenuState(context_));
	});
	world_.init("res/levels/level1.txt");
}

void GameplayState::processEvents(const sf::Event& ev){
	switch (ev.type){
	case sf::Event::MouseButtonPressed:
		if (ev.mouseButton.button == sf::Mouse::Left){
			menuButton_.press();
			world_.press();
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (ev.mouseButton.button == sf::Mouse::Left){
			if (menuButton_.release())
				menuButton_.performAction();
		}
		if (ev.mouseButton.button == sf::Mouse::Right){
			world_.setPlaneDestination(sf::Mouse::getPosition(context_.window_));
		}
		break;
	}
}

void GameplayState::updateDebug(){

}

void GameplayState::update(const sf::Time& dt){
	sf::Vector2i mousePos = sf::Mouse::getPosition(context_.window_);
	menuButton_.update(mousePos);
	world_.update(dt);
	world_.hover(mousePos);
}

void GameplayState::renderDebug() const{

}

void GameplayState::render() const{
	context_.window_.draw(mountain_);
	context_.window_.draw(world_);
	context_.window_.draw(menuButton_);
}