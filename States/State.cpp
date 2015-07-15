#include "State.h"

State::State(ChangeableContainer<State>* stateManager, sf::RenderWindow& window, bool& debug)
	:
	//active_(true),
	text_(),
	textures_(),
	fonts_(),
	context_(window,debug,stateManager){
}

State::State(const Context& context)
	:
	//active_(true),
	text_(),
	textures_(),
	fonts_(),
	context_(context){
}

State::~State(){
}