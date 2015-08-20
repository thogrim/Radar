#include "GameplayState.h"

GameplayState::GameplayState(ChangeableContainer<State>* stateManager, sf::RenderWindow& window)
	:State(stateManager,window),
	menuButton_(),
	world_(textures_,fonts_){
}

GameplayState::GameplayState(const Context& context)
	:GameplayState(context.stateManager_,context.window_){
}

GameplayState::~GameplayState(){
}

void GameplayState::init(){
	try{
		fonts_.load("calibri", "res/fonts/calibri.ttf");
		textures_.load("button", "res/img/button.png");
		//textures_.load("plane", "res/img/plane.png");
		//textures_.load("selection", "res/img/selection.png");
		textures_.load("slowplane", "res/img/slowplane.png");
		textures_.load("debug", "res/img/debug.png");
		textures_.load("fastplane", "res/img/fastplane.png");
		textures_.load("superfastplane", "res/img/superfastplane.png");
		textures_.load("mist", "res/img/mist.png");
		textures_.get("mist").setRepeated(true);
		textures_.load("bonus", "res/img/bonus.png");
	}
	catch (std::runtime_error& e){
		std::cout << e.what() << std::endl;
	}
	text_.setFont(fonts_.get("calibri"));
	text_.setCharacterSize(20);
	text_.setPosition(0, context_.window_.getSize().y-100);
	menuButton_.setTexture(textures_.get("button"));
	menuButton_.setPosition(0.f, 0.f);
	menuButton_.setAction([this](){
		context_.stateManager_->change(new MenuState(context_));
	}); 
	printButton_.setTexture(textures_.get("button"));
	printButton_.setPosition(0.f, 50.f);
	printButton_.setAction([](){
		std::cout << "stamp\n";
	});
	world_.init("res/levels/level1.txt");
}

void GameplayState::processEvents(const sf::Event& ev){
	switch (ev.type){
	case sf::Event::MouseButtonPressed:
		if (ev.mouseButton.button == sf::Mouse::Left){
			menuButton_.press();
			printButton_.press();
			world_.press();
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (ev.mouseButton.button == sf::Mouse::Left){
			if (menuButton_.release())
				menuButton_.performAction();
			else if (printButton_.release())
				printButton_.performAction();
		}
		if (ev.mouseButton.button == sf::Mouse::Right){
			world_.setPlaneDestination(sf::Mouse::getPosition(context_.window_));
		}
		break;
	}
}

void GameplayState::updateDebug(){
	text_.setString("Time passed: "+std::to_string(world_.getTimer().asSeconds()));
}

void GameplayState::update(const sf::Time& dt){
	sf::Vector2i mousePos = sf::Mouse::getPosition(context_.window_);
	menuButton_.update(mousePos);
	printButton_.update(mousePos);
	world_.update(dt);
	world_.hover(mousePos);
}

void GameplayState::renderDebug() const{
	context_.window_.draw(text_);
}

void GameplayState::render() const{
	context_.window_.draw(world_);
	context_.window_.draw(menuButton_);
	context_.window_.draw(printButton_);
}