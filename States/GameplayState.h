#pragma once

#include "State.h"
#include "MenuState.h"
#include "../GUI/Button.h"
#include "../World.h"

class GameplayState: public State{
private:
	GUI::Button menuButton_;
	//World world_;
public:
	GameplayState(ChangeableContainer<State>* stateManager, sf::RenderWindow& window);
	GameplayState(const Context& context);
	~GameplayState();

	void init();
	void processEvents(const sf::Event& ev);
	void updateDebug();
	void update(const sf::Time& dt);
	void renderDebug() const;
	void render() const;
};

