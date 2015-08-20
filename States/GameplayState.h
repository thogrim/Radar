#pragma once

#include "State.h"
#include "MenuState.h"
#include "../GUI/Button.h"
#include "../World.h"
#include "../Entities/Mountain.h"

class GameplayState: public State{
private:
	GUI::Button menuButton_;
	GUI::Button printButton_;
	World world_;
	//Mountain mountain_;
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

