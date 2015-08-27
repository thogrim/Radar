#include "MenuState.h"

MenuState::MenuState(ChangeableContainer<State>* stateManager, sf::RenderWindow& window)
	:State(stateManager,window),
	label_()
	/*button_()*/{
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
		textures_.load("menubg", "res/img/menubg.png");
		//textures_.load("root", "res/img/root.png");
		//textures_.load("child1", "res/img/child1.png");
		//textures_.load("child2", "res/img/child2.png");
		textures_.load("button", "res/img/button.png");
		textures_.load("mainmenu", "res/img/mainmenu.png");
		textures_.load("play", "res/img/play.png");
		textures_.load("instructions", "res/img/instructions.png");
		textures_.load("quit", "res/img/quit.png");
		//textures_.load("plane","res/img/plane.png");
		//textures_.load("planebutton", "res/img/planebutton.png");
		textures_.load("label2", "res/img/label2.png");
		textures_.load("checkbox", "res/img/checkbox.png");
		textures_.load("plane", "res/img/plane.png");
		textures_.load("selection", "res/img/selection.png");
	}
	catch (std::runtime_error& e){
		std::cout << e.what() << std::endl;
		//stateManager_->pop();//if there's an error in loading a resource the state will not init
	}
	text_.setFont(fonts_.get("calibri"));
	text_.setCharacterSize(20);
	text_.setPosition(0, context_.window_.getSize().y-100);
	background_.setTexture(textures_.get("menubg"));
	//background_.setPosition(0, 0);
	//testing label
	//OLD INIT CODE DOWN BELOW
	label_.setTexture(textures_.get("mainmenu"));
	label_.setPosition(context_.window_.getSize().x/2-150, 100);
	//label_.setOrigin(150.f, 0.f);
	//adding 1st button
	std::unique_ptr<GUI::Button> playButton(new GUI::Button());
	playButton->setTexture(textures_.get("play"));
	playButton->setPosition(50, 150);
	playButton->setAction([this](){
		context_.stateManager_->change(new GameplayState(context_));
	});
	label_.attachComponent(std::move(playButton));
	//adding 2nd button
	std::unique_ptr<GUI::Button> instrButton(new GUI::Button());
	instrButton->setTexture(textures_.get("instructions"));
	instrButton->setPosition(50, 200);
	instrButton->setAction([this](){
		context_.stateManager_->change(new TitleState(context_));
		//std::cout << plane_.getWorldPosition().x << " " << plane_.getWorldPosition().y << std::endl;
	});
	label_.attachComponent(std::move(instrButton));
	//adding 3rd button
	std::unique_ptr<GUI::Button> quitButton(new GUI::Button());
	quitButton->setTexture(textures_.get("quit"));
	quitButton->setPosition(50, 250);
	quitButton->setAction([this](){
		context_.stateManager_->pop();
	});
	label_.attachComponent(std::move(quitButton));
	//adding checkbox
	std::unique_ptr<GUI::Checkbox> checkbox1(new GUI::Checkbox());
	//checkbox1->setTexture(textures_.get("checkbox"));
	//checkbox1->setPosition(50, 150);
	//checkbox1->setToggleAction([this](){
	//	std::cout << "checkbox toggled\n";
	//});
	//checkbox1->setUntoggleAction([this](){
	//	std::cout << "checkbox untoggled\n";
	//});
	//label_.attachComponent(std::move(checkbox1));
	//adding standalone button
	//button_.setTexture(textures_.get("button"));
	//button_.setPosition(600, 0);
	//button_.setAction([](){
	//	std::cout << "standalone button action\n";
	//});
	//entity_.create(textures_.get("button"),0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f);
	//entity_.setPosition(100,100);
	//entity_.setTexture(textures_.get("plane"));
	//std::unique_ptr<Entity> ptr(new Entity(textures_.get("plane")));
	//planes_.push_back(std::move(ptr));
	//planes_.back()->setPosition(100, 500);
	//std::unique_ptr<Entity> en(new Entity(textures_.get("plane")));
}

void MenuState::processEvents(const sf::Event& ev){
	switch (ev.type){
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::Return)
			context_.stateManager_->change(new TitleState(context_));
		//else if (ev.key.code == sf::Keyboard::Q)
		//	doAction();
		break;
	case sf::Event::MouseButtonPressed:
		if (ev.mouseButton.button == sf::Mouse::Left){
			label_.press();
			//button_.press();
			//if (!plane_.selected())
			//	plane_.select();
			//else
			//	plane_.unselect();
		}
		//else if (ev.mouseButton.button == sf::Mouse::Right)
			//if (plane_.selected())
			//	plane_.setDestination(sf::Mouse::getPosition(context_.window_));
		break;
	case sf::Event::MouseButtonReleased:
		if (ev.mouseButton.button == sf::Mouse::Left){
			if (label_.release())
				label_.performAction();
			//else if (button_.release())
			//	button_.performAction();
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
	//text_.setString("button pressed: " + std::to_string(nButton()));
}

void MenuState::update(const sf::Time& dt){
	updateDebug();
	//context_.stateManager_->change(new TitleState(context_));
	//testing button
	//updateButtons();
	sf::Vector2i mousePos = sf::Mouse::getPosition(context_.window_);
	label_.update(mousePos);
	//button_.update(mousePos);
	/*entity_.update(dt);
	planes_.back()->update(dt);*/
}

void MenuState::renderDebug() const{
	context_.window_.draw(text_);
}

void MenuState::render() const{
	context_.window_.draw(background_);
	context_.window_.draw(label_);
	//context_.window_.draw(button_);
	/*context_.window_.draw(entity_);
	planes_.back()->draw(context_.window_, sf::RenderStates::Default);*/
}

//old init code
//label_.create(textures_.get("label2"), 0, 0);
//label_.createButton(textures_.get("button"),50,50,
//	[this](){
//	context_.stateManager_->change(new TitleState(context_));
//});
//label_.createButton(textures_.get("button"), 50, 100,
//	[this](){
//	std::cout << plane_.getRotation() << std::endl;
//});
//label_.createCheckbox(textures_.get("checkbox"), 50, 150,
//	[](){
//	std::cout << "checkbox toggled\n";
//},
//	[](){
//	std::cout << "checkbox untoggled\n";
//});
//label_.createCheckbox(textures_.get("checkbox"), 100, 150,
//	[](){
//	std::cout << "checkbox toggled\n";
//},
//	[](){
//	std::cout << "checkbox untoggled\n";
//});
//label_.createCheckbox(textures_.get("checkbox"), 50, 200,
//	[](){
//	std::cout << "checkbox toggled\n";
//},
//	[](){
//	std::cout << "checkbox untoggled\n";
//});
//label_.createCheckbox(textures_.get("checkbox"), 100, 200,
//	[](){
//	std::cout << "checkbox toggled\n";
//},
//	[](){
//	std::cout << "checkbox untoggled\n";
//});