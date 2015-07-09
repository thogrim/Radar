#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

class Application
{
private:
	//WINDOW PROPERTIES
	int width_;
	int height_;
	std::string title_;
	float fps_;

	sf::RenderWindow window_;

	//DEBUG INFO
	bool debugMode_;
	sf::Font debugFont_;
	sf::Text text_;
	double currentFps_;
	double currentUps_;
	int updatesCounter_;
	int frameCounter_;
	sf::Time timePassed_;

public:
	//CONSTRUCTORS & DESTRUCTOR
	Application(int width, int height, const std::string& title, float fps, bool debugMode);
	Application();
	~Application();

	//PRIVATE METHODS
	void processEvents();
	void update(const sf::Time& dt);
	void updateDebug();
	void renderDebug();
	void render();

	//PUBLIC METHODS
	void run();
};

