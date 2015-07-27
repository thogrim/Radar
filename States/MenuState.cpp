#include "MenuState.h"

MenuState::MenuState(ChangeableContainer<State>* stateManager, sf::RenderWindow& window)
	:State(stateManager,window)/*,
	buttons_()*/{
}

MenuState::MenuState(const Context& context)
	:MenuState(context.stateManager_,context.window_){
}

MenuState::~MenuState(){
	std::cout << "Menu State destroyed\n";
}

void MenuState::init(){
	try{
		fonts_.load("calibri", "res/fonts/calibri.ttf");
		textures_.load("menuImage", "res/img/menuScreen.png");
		//textures_.load("root", "res/img/root.png");
		//textures_.load("child1", "res/img/child1.png");
		//textures_.load("child2", "res/img/child2.png");
		textures_.load("button","res/img/button.png");
		textures_.load("plane","res/img/plane.png");
		textures_.load("planebutton", "res/img/planebutton.png");
	}
	catch (std::runtime_error& e){
		std::cout << e.what() << std::endl;
		//stateManager_->pop();//if there's an error in loading a resource the state will not init
	}
	text_.setFont(fonts_.get("calibri"));
	text_.setCharacterSize(20);
	text_.setPosition(0, context_.window_.getSize().y-100);
	background_.setTexture(textures_.get("menuImage"));
	background_.setPosition(100, 100);
	//testing button & entity
	createButton(textures_.get("button"), 300, 300,
		[this](){
		context_.stateManager_->change(new TitleState(context_));
	});
}

void MenuState::processEvents(const sf::Event& ev){
	switch (ev.type){
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::Return)
			context_.stateManager_->change(new TitleState(context_));
		else if (ev.key.code == sf::Keyboard::Q)
			doAction();
		break;
	case sf::Event::MouseButtonPressed:
		if (ev.mouseButton.button == sf::Mouse::Left){
			pressButton();
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (ev.mouseButton.button == sf::Mouse::Left){
			registerAction();
		}
		break;
		//for scene testing
		/*if (ev.key.code == sf::Keyboard::Up)
			root_.move(0, -10);
		if (ev.key.code == sf::Keyboard::Down)
			root_.move(0, 10);
		if (ev.key.code == sf::Keyboard::Left)
			root_.move(-10, 0);
		if (ev.key.code == sf::Keyboard::Right)
			root_.move(10, 0);*/
	}
} 

void MenuState::updateDebug(){
	//text_.setString("button pos: " + std::to_string(button_.getPosition().x) + " " + std::to_string(button_.getPosition().y));
	/*if (button_.hovered())
		text_.setString("button hovered");
	else
		text_.setString("button not hovered");*/
	text_.setString("button pressed: " + std::to_string(nButton()));
}

void MenuState::update(const sf::Time& dt){
	updateDebug();
	//context_.stateManager_->change(new TitleState(context_));
	//testing button
	updateButtons();

	performAction();
}

void MenuState::renderDebug() const{
	context_.window_.draw(text_);
}

void MenuState::render() const{
	context_.window_.draw(background_);
	//testing button
	drawButtons();
}