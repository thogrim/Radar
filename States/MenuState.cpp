#include "MenuState.h"

MenuState::MenuState(ChangeableContainer<State>* stateManager, sf::RenderWindow& window)
	:State(stateManager,window){
}

MenuState::MenuState(const Context& context)
	:State(context){
}

MenuState::~MenuState(){
}

void MenuState::init(){
	try{
		fonts_.load("calibri", "res/fonts/calibri.ttf");
		textures_.load("menuImage", "res/img/menuScreen.png");
		textures_.load("root", "res/img/root.png");
		textures_.load("child1", "res/img/child1.png");
		textures_.load("child2", "res/img/child2.png");
	}
	catch (std::runtime_error& e){
		std::cout << e.what() << std::endl;
		//stateManager_->pop();//if there's an error in loading a resource the state will not init
	}
	text_.setFont(fonts_.get("calibri"));
	text_.setCharacterSize(20);
	text_.setPosition(100, 100);
	text_.setString("Menu! Yay!");
	background_.setTexture(textures_.get("menuImage"));
	//testing scene
	/*root_.setTexture(textures_.get("root"));
	root_.setPosition(600, 400);
	std::unique_ptr<SceneNode> child1(new SceneNode());
	child1->setTexture(textures_.get("child1"));
	child1->setPosition(100, 100);
	root_.attachChild(std::move(child1));
	std::unique_ptr<SceneNode> child2(new SceneNode());
	child2->setTexture(textures_.get("child2"));
	child2->setPosition(-100, -100);
	root_.attachChild(std::move(child2));*/
	//view_.setViewport(sf::FloatRect(0.25f,0.25f,0.5f,0.5f));
}

void MenuState::processEvents(const sf::Event& ev){
	switch (ev.type){
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::Return)
			context_.stateManager_->change(new TitleState(context_));
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

}

void MenuState::update(const sf::Time& dt){

}

void MenuState::renderDebug() const{

}

void MenuState::render() const{
	//sf::View defaultView = target.getDefaultView();
	//target.setView(view_);
	context_.window_.draw(background_);
	//target.setView(defaultView);
}