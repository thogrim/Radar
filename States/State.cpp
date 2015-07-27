#include "State.h"

State::State(ChangeableContainer<State>* stateManager, sf::RenderWindow& window)
	:context_(window,stateManager),
	text_(),
	textures_(),
	fonts_(),
	background_(),
	pressedButton_(-1),
	buttons_(),
	actions_(),
	action_(-1){
}

State::State(const Context& context)
	:State(context.stateManager_,context.window_){
}

State::~State(){
}

void State::createButton(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action){
	buttons_.push_back(GUI::Button(texture, posX, posY));
	buttons_.back().action_ = action;
	actions_.push_back(action);
}

void State::updateButtons(){
	for (GUI::Button& b : buttons_){
		b.update(sf::Mouse::getPosition(context_.window_));
	}
}

void State::pressButton(){
	int i = 0;
	for (GUI::Button& b : buttons_){
		if (b.press()){
			pressedButton_ = i;
			break;
		}
		++i;
	}
}

void State::registerAction(){
	if (pressedButton_ >= 0){
		if (buttons_[pressedButton_].hovered() && buttons_[pressedButton_].pressed()){
			action_ = pressedButton_;
			buttons_[pressedButton_].release();
			pressedButton_ = -1;
		}
		else if (!buttons_[pressedButton_].hovered()){
			buttons_[pressedButton_].release();
			pressedButton_ = -1;
		}
	}
}

void State::performAction(){
	if (action_ >= 0){
		int temp = action_;
		action_ = -1;
		actions_[temp]();
	}
}

void State::drawButtons() const{
	for (const GUI::Button& b : buttons_){
		context_.window_.draw(b);
	}
}