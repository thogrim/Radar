#pragma once

#include "State.h"
#include "TitleState.h"
#include "../ChangeableContainer.h"

class MenuState : public State
{
public:
	MenuState(ChangeableContainer<State>* stateManager);
	~MenuState();

	void init();
	void processEvents(const sf::Event& ev);
	void update(const sf::Time& dt);
};