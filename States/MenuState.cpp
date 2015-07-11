#include "MenuState.h"


MenuState::MenuState(ChangeableContainer<State>* stateManager)
	:State(stateManager){
}


MenuState::~MenuState(){
}

void MenuState::init(){
	if (!font_.loadFromFile("res/fonts/calibri.ttf")){
		//ERROR IN LOADING FONT
		//TODO: HANDLE IT!
		//std::cout << "error in loading debug font\n";
	}
	text_.setFont(font_);
	text_.setCharacterSize(20);
	text_.setString("Menu! Yay!");
	text_.setPosition(200, 100);
}

void MenuState::processEvents(const sf::Event& ev){
	switch (ev.type){
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::Return)
			stateManager_->pendChange(Action::SWITCH, new TitleState(stateManager_));
	}
}

void MenuState::update(const sf::Time& dt){

}
