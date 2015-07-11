#include "TitleState.h"


TitleState::TitleState(ChangeableContainer<State>* stateManager)
	:State(stateManager),
	titleDuration(sf::seconds(1.0f)),
	timer(sf::Time::Zero){
}


TitleState::~TitleState(){
}

void TitleState::init(){
	if (!font_.loadFromFile("res/fonts/calibri.ttf")){
		//ERROR IN LOADING FONT
		//TODO: HANDLE IT!
		//std::cout << "error in loading debug font\n";
	}
	text_.setFont(font_);
	text_.setCharacterSize(20);
	text_.setString("Title! Yay!");
	text_.setPosition(100, 100);
}

void TitleState::processEvents(const sf::Event& ev){
	switch (ev.type){
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::Return)
			stateManager_->pendChange(Action::SWITCH,new MenuState(stateManager_));
	}
}

void TitleState::update(const sf::Time& dt){
	timer += dt;
	if (timer>titleDuration)
		stateManager_->pendChange(Action::SWITCH, new MenuState(stateManager_));
}
