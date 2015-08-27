#include "GameplayState.h"

GameplayState::GameplayState(ChangeableContainer<State>* stateManager, sf::RenderWindow& window)
	:State(stateManager,window),
	menuLabel_(),
	world_(textures_,fonts_){
}

GameplayState::GameplayState(const Context& context)
	:GameplayState(context.stateManager_,context.window_){
}

GameplayState::~GameplayState(){
}

void GameplayState::init(){
	try{
		fonts_.load("calibri", "res/fonts/calibri.ttf");
		//textures_.load("button", "res/img/button.png");
		//textures_.load("plane", "res/img/plane.png");
		//textures_.load("selection", "res/img/selection.png");
		textures_.load("pause", "res/img/pause.png");
		textures_.load("backtomenu", "res/img/backtomenu.png");
		textures_.load("continue", "res/img/continue.png");
		textures_.load("slowplane", "res/img/slowplane.png");
		textures_.load("debug", "res/img/debug.png");
		textures_.load("fastplane", "res/img/fastplane.png");
		textures_.load("superfastplane", "res/img/superfastplane.png");
		textures_.load("mist", "res/img/mist.png");
		textures_.get("mist").setRepeated(true);
		textures_.load("bonus", "res/img/bonus.png");
	}
	catch (std::runtime_error& e){
		std::cout << e.what() << std::endl;
	}
	text_.setFont(fonts_.get("calibri"));
	text_.setCharacterSize(20);
	text_.setPosition(0, context_.window_.getSize().y-100);
	//menuButton_.setTexture(textures_.get("button"));
	//menuButton_.setPosition(0.f, 0.f);
	//menuButton_.setAction([this](){
	//	context_.stateManager_->change(new MenuState(context_));
	//}); 
	//printButton_.setTexture(textures_.get("button"));
	//printButton_.setPosition(0.f, 50.f);
	//printButton_.setAction([](){
	//	std::cout << "stamp\n";
	//});
	menuLabel_.setTexture(textures_.get("pause"));
	menuLabel_.setPosition(context_.window_.getSize().x / 2 - 150, 100);
	//	continue button
	std::unique_ptr<GUI::Button> continueButton(new GUI::Button());
	continueButton->setTexture(textures_.get("continue"));
	continueButton->setPosition(50, 100);
	continueButton->setAction([this](){
		menuLabel_.setActive(false);
	});
	menuLabel_.attachComponent(std::move(continueButton));
	//	back to menu button
	std::unique_ptr<GUI::Button> backButton(new GUI::Button());
	backButton->setTexture(textures_.get("backtomenu"));
	backButton->setPosition(50, 150);
	backButton->setAction([this](){
		context_.stateManager_->change(new MenuState(context_));
	});
	menuLabel_.attachComponent(std::move(backButton));
	//
	menuLabel_.setActive(false);
	world_.init("res/levels/level1.txt");
}

void GameplayState::processEvents(const sf::Event& ev){
	switch (ev.type){
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::D){
			world_.setDrawingDestinations();
		}
		if (ev.key.code == sf::Keyboard::P){
			menuLabel_.setActive(true);
		}
		break;
	case sf::Event::MouseButtonPressed:
		if (ev.mouseButton.button == sf::Mouse::Left){
			if (menuLabel_.isActive())
				menuLabel_.press();
			else
				world_.press();
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (ev.mouseButton.button == sf::Mouse::Left){
			if (menuLabel_.isActive() && menuLabel_.release())
				menuLabel_.performAction();
		}
		if (ev.mouseButton.button == sf::Mouse::Right){
			world_.setPlaneDestination(sf::Mouse::getPosition(context_.window_));
		}
		break;
	}
}

void GameplayState::updateDebug(){
	text_.setString("Time passed: "+std::to_string(world_.getTimer().asSeconds()));
}

void GameplayState::update(const sf::Time& dt){
	sf::Vector2i mousePos = sf::Mouse::getPosition(context_.window_);
	if (menuLabel_.isActive())
		menuLabel_.update(mousePos);
	else{
		world_.update(dt);
		world_.hover(mousePos);
	}
}

void GameplayState::renderDebug() const{
	context_.window_.draw(text_);
}

void GameplayState::render() const{
	context_.window_.draw(world_);
	if (menuLabel_.isActive())
		context_.window_.draw(menuLabel_);
}