#include "StateManager.h"

StateManager::StateManager(sf::RenderWindow& window) :
	stateStack_(),
	window_(window),
	//font_(),
	text_(){
	if (!font_.loadFromFile("res/fonts/calibri.ttf")){
		std::cout << "StateManager could not load his font from file\n";
	}
	text_.setFont(font_);
	text_.setCharacterSize(20);
	text_.setPosition(0, window_.getSize().y - 75);
	stateStack_.push_back(std::unique_ptr<State>(new TitleState(this,window_)));
	stateStack_.back()->init();
}

void StateManager::pop(){
	stateStack_.pop_back();
}

void StateManager::push(State* state){
	stateStack_.push_back(std::unique_ptr<State>(state));
	stateStack_.back()->init();
}

void StateManager::change(State* state){
	stateStack_.pop_back();
	stateStack_.push_back(std::unique_ptr<State>(state));
	stateStack_.back()->init();
}

void StateManager::processEvents(const sf::Event& ev){
	stateStack_.back()->processEvents(ev);
}

void StateManager::updateDebug(){
	text_.setString("Current state stack size: " + std::to_string(stateStack_.size()));
	stateStack_.back()->updateDebug();
}

void StateManager::update(const sf::Time& dt){
	updateDebug();
	stateStack_.back()->update(dt);
}

void StateManager::renderDebug() const {
	if (!stateStack_.empty()){
		window_.draw(text_);
		stateStack_.back()->renderDebug();
	}
}

void StateManager::render() const{
	//drawing state on top of stack
	if (!stateStack_.empty())
		stateStack_.back()->render();
	//later it might need to draw multiple states
}