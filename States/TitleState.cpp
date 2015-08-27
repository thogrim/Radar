#include "TitleState.h"

TitleState::TitleState(ChangeableContainer<State>* stateManager, sf::RenderWindow& window)
	:State(stateManager,window),
	title_(){
}

TitleState::TitleState(const Context& context)
	:TitleState(context.stateManager_, context.window_){
}

TitleState::~TitleState(){
	//std::cout << "Title state destroyed\n";
}

void TitleState::init(){
	try{
		fonts_.load("calibri", "res/fonts/calibri.ttf");
		textures_.load("title", "res/img/title.png");
	}
	catch (std::runtime_error& e){
		std::cout << e.what() << std::endl;
		//stateManager_->pop();//if there's an error in loading a resource the state will not init
	}
	title_.setFont(fonts_.get("calibri"));
	title_.setCharacterSize(40);
	title_.setPosition(context_.window_.getSize().x/2-60.f, 100.f);
	title_.setString("RADAR");
	title_.setColor(sf::Color(0, 0, 0));
	title_.setStyle(sf::Text::Bold);

	text_.setFont(fonts_.get("calibri"));
	text_.setCharacterSize(20);
	text_.setPosition(260.f, context_.window_.getSize().y-50.f);
	text_.setString("Press any key or click to continue");
	text_.setColor(sf::Color(0, 0, 0));
	//loading background image
	background_.setTexture(textures_.get("title"));
}

void TitleState::processEvents(const sf::Event& ev){
	switch (ev.type){
	case sf::Event::KeyPressed:
		//if (ev.key.code == sf::Keyboard::Return)
		context_.stateManager_->change(new MenuState(context_));
		break;
	case sf::Event::MouseButtonPressed:
		context_.stateManager_->change(new MenuState(context_));
		break;
	}
}

void TitleState::updateDebug(){

}

void TitleState::update(const sf::Time& dt){
	//timer_ += dt;
	//if (timer_>titleDuration_)
	//	context_.stateManager_->change(new MenuState(context_));
}

void TitleState::renderDebug() const{

}

void TitleState::render() const{
	context_.window_.draw(background_);
	context_.window_.draw(text_);
	context_.window_.draw(title_);
}
