#include "State.h"


State::State(ChangeableContainer<State>* stateManager)
	:stateManager_(stateManager),
	text_()
	{
	//if (!font_.loadFromFile("res/fonts/calibri.ttf")){
	//	//ERROR IN LOADING FONT
	//	//TODO: HANDLE IT!
	//	std::cout << "error in loading debug font\n";
	//}
	//text_.setFont(font_);
	//text_.setCharacterSize(20);
}


State::~State(){
}

sf::Text State::getText() const {
	return text_;
}