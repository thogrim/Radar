#include "Application.h"

Application::Application(int width, int height, const std::string& title, float fps, bool debugMode):
	width_(width),
	height_(height),
	title_(title),
	fps_(fps),
	debugMode_(debugMode),
	window_(sf::VideoMode(width_,height_,32), title_),
	stateManager_(window_),
	//DEBUG
	text_(),
	currentFps_(fps_),
	updatesCounter_(0),
	frameCounter_(0),
	timePassed_(sf::Time::Zero),
	circle_(30,20),
	circleSpeed_(100),
	timePerDebugUpdate_(sf::seconds(0.5f)),
	mouse_()
{
	window_.setFramerateLimit(fps_);
	window_.setKeyRepeatEnabled(false);// nie generuje eventu KeyPressed gdy klawisz jest wciœniêty :)
	if (!debugFont_.loadFromFile("res/fonts/calibri.ttf")){
		//ERROR IN LOADING FONT
		//TODO: HANDLE IT!
		std::cout << "error in loading debug font\n";
	}
	text_.setFont(debugFont_);
	text_.setCharacterSize(20);
	text_.setPosition(0, height_ - 50);
	mouse_.setFont(debugFont_);
	mouse_.setCharacterSize(20);
	mouse_.setPosition(window_.getSize().x >> 1, window_.getSize().y - 75);
	//stateManager_.push(new MenuState());
	circle_.setFillColor(sf::Color::White);
	circle_.setPosition(window_.getSize().x-2*circle_.getRadius(),0);
}


Application::Application() : Application(800, 600, "SFML Game", 60, false) {
}


Application::~Application(){
}

void Application::processEvents(){
/*
TODO zmiana rozmiaru okna lub zablokowanie?
*/
	sf::Event ev;
	while (window_.pollEvent(ev)){
		switch (ev.type){
		case sf::Event::Closed:
			window_.close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				window_.close();
			else if (ev.key.code == sf::Keyboard::Tab)
				debugMode_ = true;
			else
				stateManager_.processEvents(ev);
			break;
		//default:
		//	stateManager_.processEvents(ev);
		case sf::Event::KeyReleased:
			if (ev.key.code == sf::Keyboard::Tab)
				debugMode_ = false;
			break;
		case sf::Event::MouseButtonPressed:
			//if (ev.mouseButton.button==sf::Mouse::Left)
				stateManager_.processEvents(ev);
			break;
		case sf::Event::MouseButtonReleased:
			//if (ev.mouseButton.button == sf::Mouse::Left)
				stateManager_.processEvents(ev);
			break;
		}
	}
}

void Application::updateDebug(const sf::Time& dt){
	//circle
	circle_.move(0, circleSpeed_*dt.asSeconds());
	if (circle_.getPosition().y > window_.getSize().y - 2 * circle_.getRadius())
		circleSpeed_ = -circleSpeed_;
	else if (circle_.getPosition().y < 0)
		circleSpeed_ = -circleSpeed_;

	//mouse
	sf::Vector2i mousePos(sf::Mouse::getPosition(window_));
	mouse_.setString("mouse position:\nx: "+std::to_string(mousePos.x)+"\ny: "+std::to_string(mousePos.y));

	//fps, ups
	if (timePassed_ > timePerDebugUpdate_){
		currentFps_ = frameCounter_ / timePassed_.asSeconds();
		currentUps_ = updatesCounter_ / timePassed_.asSeconds();
		frameCounter_ = 0;
		updatesCounter_ = 0;
		timePassed_ = sf::Time::Zero;
		std::ostringstream oss;
		oss << "FPS: " << std::setprecision(3) << currentFps_ << "\nUPS: " << std::setprecision(4) << currentUps_;
		text_.setString(oss.str());
	}
}

void Application::update(const sf::Time& dt){
	if (!stateManager_.empty()){
		stateManager_.update(dt);
		updateDebug(dt);
	}
	else
		window_.close();

}

void Application::renderDebug(){
	window_.draw(text_);
	window_.draw(mouse_);
	window_.draw(circle_);
	stateManager_.renderDebug();
}

void Application::render(){
	window_.clear(sf::Color::Black);
	stateManager_.render();
	if (debugMode_)
		renderDebug();
	window_.display();
}

void Application::run(){
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	const sf::Time TimePerUpdate = sf::seconds(1.f / 240.0f);
	//const sf::Time TimePerDebugUpdate = sf::seconds(.5f);
	//float alpha
	while (window_.isOpen()){
		processEvents();
		accumulator += clock.restart();
		timePassed_ += accumulator;
		++frameCounter_;
		while (accumulator > TimePerUpdate && window_.isOpen()){
			accumulator -= TimePerUpdate;
			processEvents();
			update(TimePerUpdate);
			++updatesCounter_;
		}
		//updating when some time is left in accumulator
		update(accumulator);
		++updatesCounter_;

		render();
	}
}