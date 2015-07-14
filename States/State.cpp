#include "State.h"

State::State(ChangeableContainer<State>* stateManager, sf::RenderWindow& window, bool& debug)
	:stateManager_(stateManager),
	//active_(true),
	text_(),
	textures_(),
	fonts_(),
	context_(window,debug){
}

State::State(ChangeableContainer<State>* stateManager, const Context& context)
	:stateManager_(stateManager),
	//active_(true),
	text_(),
	textures_(),
	fonts_(),
	context_(context){
}

State::~State(){
}