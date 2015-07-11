#pragma once

#include "State.h"
#include "MenuState.h"
#include "../ChangeableContainer.h"

class TitleState : public State
{
private:
	const sf::Time titleDuration;
	sf::Time timer;
public:
	TitleState(ChangeableContainer<State>* stateManager);
	~TitleState();

	void init();
	void processEvents(const sf::Event& ev);
	void update(const sf::Time& dt);
};