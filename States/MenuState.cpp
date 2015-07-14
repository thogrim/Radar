#include "MenuState.h"

MenuState::MenuState(ChangeableContainer<State>* stateManager, sf::RenderWindow& window, bool& debug)
	:State(stateManager,window,debug),
	bgImage_()
	//view_(sf::FloatRect(0,0,800,600))
{
}

MenuState::MenuState(ChangeableContainer<State>* stateManager, const Context& context)
	:State(stateManager, context),
	bgImage_()
	//view_(sf::FloatRect(0,0,800,600))
{
}

MenuState::~MenuState(){
}

void MenuState::init(){
	try{
		fonts_.load("calibri", "res/fonts/calibri.ttf");
		textures_.load("menuImage", "res/img/menuScreen.png");
	}
	catch (std::runtime_error& e){
		std::cout << e.what() << std::endl;
		//stateManager_->pop();//if there's an error in loading a resource the state will not init
	}
	text_.setFont(fonts_.get("calibri"));
	text_.setCharacterSize(20);
	text_.setPosition(100, 100);
	text_.setString("Menu! Yay!");
	bgImage_.setTexture(textures_.get("menuImage"));
	//view_.setViewport(sf::FloatRect(0.25f,0.25f,0.5f,0.5f));
}

void MenuState::processEvents(const sf::Event& ev){
	switch (ev.type){
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::Return)
			stateManager_->change(new TitleState(stateManager_, context_));
	}
}

void MenuState::updateDebug(){

}

void MenuState::update(const sf::Time& dt){

}

void MenuState::renderDebug() const{

}

void MenuState::render() const{
	//sf::View defaultView = target.getDefaultView();
	//target.setView(view_);
	context_.window_.draw(bgImage_);
	//target.setView(defaultView);
}