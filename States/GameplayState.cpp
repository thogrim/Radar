#include "GameplayState.h"

GameplayState::GameplayState(ChangeableContainer<State>* stateManager, sf::RenderWindow& window)
	:State(stateManager,window),
	menuButton_(){
}

GameplayState::GameplayState(const Context& context)
	:GameplayState(context.stateManager_,context.window_){
}

GameplayState::~GameplayState(){
}

void GameplayState::init(){
	try{
		textures_.load("button", "res/img/button.png");
	}
	catch (std::runtime_error& e){
		std::cout << e.what() << std::endl;
	}
	menuButton_.setTexture(textures_.get("button"));
	menuButton_.setPosition(300, 200);
	menuButton_.setAction([this](){
		context_.stateManager_->change(new MenuState(context_));
	});
}

void GameplayState::processEvents(const sf::Event& ev){
	switch (ev.type){
	case sf::Event::MouseButtonPressed:
		if (ev.mouseButton.button == sf::Mouse::Left){
			menuButton_.press();
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (ev.mouseButton.button == sf::Mouse::Left){
			if (menuButton_.release())
				menuButton_.performAction();
		}
		break;
	}
}

void GameplayState::updateDebug(){

}

void GameplayState::update(const sf::Time& dt){
	sf::Vector2i mousePos = sf::Mouse::getPosition(context_.window_);
	menuButton_.update(mousePos);
}

void GameplayState::renderDebug() const{

}

void GameplayState::render() const{
	context_.window_.draw(menuButton_);
}