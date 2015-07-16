#include "TitleState.h"

TitleState::TitleState(ChangeableContainer<State>* stateManager, sf::RenderWindow& window, bool& debug)
	:State(stateManager,window,debug),
	titleDuration_(sf::seconds(1.0f)),
	timer_(sf::Time::Zero){
}

TitleState::TitleState(const Context& context)
	:State(context),
	titleDuration_(sf::seconds(1.0f)),
	timer_(sf::Time::Zero){
}

TitleState::~TitleState(){
}

void TitleState::init(){
	try{
		fonts_.load("calibri", "res/fonts/calibri.ttf");
		textures_.load("titleImage", "res/img/titleScreen.png");
	}
	catch (std::runtime_error& e){
		std::cout << e.what() << std::endl;
		//stateManager_->pop();//if there's an error in loading a resource the state will not init
	}
	text_.setFont(fonts_.get("calibri"));
	text_.setCharacterSize(20);
	text_.setPosition(100, 100);
	text_.setString("Title! Yay!");
	//loading background image
	SpriteNode* bg = new SpriteNode(textures_.get("titleImage"));
	background_ = std::unique_ptr<SpriteNode>(std::move(bg));
}

void TitleState::processEvents(const sf::Event& ev){
	switch (ev.type){
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::Return)
			context_.stateManager_->change(new MenuState(context_));
	}
}

void TitleState::updateDebug(){

}

void TitleState::update(const sf::Time& dt){
	timer_ += dt;
	if (timer_>titleDuration_)
		context_.stateManager_->change(new MenuState(context_));
}

void TitleState::renderDebug() const{

}

void TitleState::render() const{
	context_.window_.draw(*background_);
}
