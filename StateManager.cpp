#include "StateManager.h"


StateManager::StateManager():
	stateStack_(),
	pendingChange_(Action::NONE,nullptr){
	stateStack_.push(std::unique_ptr<State>(new TitleState(this)));
	stateStack_.top()->init();
}


StateManager::~StateManager(){
}

void StateManager::pendChange(Action action, State* state){
	pendingChange_.action_ = action;
	pendingChange_.state_ = state;
}

void StateManager::processEvents(const sf::Event& ev){
	stateStack_.top()->processEvents(ev);
}

void StateManager::update(const sf::Time& dt){
	if (changeRequested()){
		switch (pendingChange_.action_){
		case Action::SWITCH:
			stateStack_.pop();
			stateStack_.push(std::unique_ptr<State>(pendingChange_.state_));
			stateStack_.top()->init();
			break;
		}
		resetChange();
	}
	else{
		stateStack_.top()->update(dt);
	}
}

sf::Text StateManager::getDrawable() const{
	return stateStack_.top()->getText();
}
