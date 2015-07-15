#pragma once

#include "State.h"
#include "MenuState.h"
#include "../ChangeableContainer.h"

class TitleState : public State
{
private:
	const sf::Time titleDuration_;
	sf::Time timer_;

	sf::Sprite bgImage_;
public:
	TitleState(ChangeableContainer<State>* stateManager, sf::RenderWindow& window, bool& debug);
	TitleState(const Context& context);
	~TitleState();

	void init();
	void processEvents(const sf::Event& ev);
	void updateDebug();
	void update(const sf::Time& dt);
	void renderDebug() const;
	void render() const;
};