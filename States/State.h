#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../ChangeableContainer.h"

class State{
protected:
	//POINTER TO STATE MANAGER
	ChangeableContainer<State>* stateManager_;

	//DRAWABLE STUFF
	//Scene scene_;
	sf::Font font_;
	sf::Text text_;

public:
	State(ChangeableContainer<State>* stateManager);
	~State();

	sf::Text getText() const;

	virtual void init() = 0;
	virtual void processEvents(const sf::Event& ev)=0;
	virtual void update(const sf::Time& dt)=0;
};

