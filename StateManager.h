#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "States/State.h"
#include "States/TitleState.h"
#include "States/MenuState.h"
#include "ChangeableContainer.h"

class StateManager: public ChangeableContainer<State>
{
private:
	//STATE STACK
	std::vector<std::unique_ptr<State>> stateStack_;

	sf::RenderWindow& window_;

	//DEBUG TEXT
	sf::Font font_;
	sf::Text text_;

	void updateDebug();
public:
	StateManager(sf::RenderWindow& window);
	virtual ~StateManager(){}

	bool empty(){
		return stateStack_.empty();
	}

	void pop();
	void push(State* state);
	void change(State* state);

	void processEvents(const sf::Event& ev);
	void update(const sf::Time& dt);
	void renderDebug() const;
	void render() const;
};

