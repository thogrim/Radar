#include "Application.h"

Application::Application(int width, int height, const std::string& title, float fps, bool debugMode):
	width_(width),
	height_(height),
	title_(title),
	fps_(fps),
	debugMode_(debugMode),
	window_(sf::VideoMode(width_,height_,32), title_),
	stateManager_(window_,debugMode_),
	//DEBUG
	text_(),
	currentFps_(fps_),
	updatesCounter_(0),
	frameCounter_(0),
	timePassed_(sf::Time::Zero)
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
	//stateManager_.push(new MenuState());
}


Application::Application() : Application(800, 600, "SFML Game", 60, true) {
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
		default:
			stateManager_.processEvents(ev);
		case sf::Event::KeyReleased:
			if (ev.key.code == sf::Keyboard::Tab)
				debugMode_ = false;
		}
	}
}

void Application::update(const sf::Time& dt){
	if (!stateManager_.empty())
		stateManager_.update(dt);
	else
		window_.close();
}

void Application::updateDebug(){
	currentFps_ = frameCounter_ / timePassed_.asSeconds();
	currentUps_ = updatesCounter_ / timePassed_.asSeconds();
	frameCounter_ = 0;
	updatesCounter_ = 0;
	timePassed_ = sf::Time::Zero;
	std::ostringstream oss;
	oss << "FPS: " << std::setprecision(3) << currentFps_ << "\nUPS: " << std::setprecision(4) << currentUps_;
	text_.setString(oss.str());
}

void Application::renderDebug(){
	window_.draw(text_);
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
	const sf::Time TimePerDebugUpdate = sf::seconds(.5f);
	//float alpha
	while (window_.isOpen()){
		processEvents();
		accumulator += clock.restart();
		timePassed_ += accumulator;
		++frameCounter_;
		while (accumulator > TimePerUpdate){
			accumulator -= TimePerUpdate;
			processEvents();
			update(TimePerUpdate);
			++updatesCounter_;
		}
		//updating when some time is left in accumulator
		update(accumulator);
		++updatesCounter_;
		
		if (timePassed_ > TimePerDebugUpdate){
			updateDebug();
		}

		render();
	}
}