#include "State.h"

State::State(ChangeableContainer<State>* stateManager, sf::RenderWindow& window)
	:context_(window,stateManager),
	text_(),
	textures_(),
	fonts_(),
	background_(){
}

State::State(const Context& context)
	:State(context.stateManager_,context.window_){
}

State::~State(){
}