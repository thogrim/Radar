#pragma once

#include "State.h"
#include "TitleState.h"
#include "../ChangeableContainer.h"

class MenuState : public State
{
private:
	sf::Sprite bgImage_;
	//sf::View view_;
	
public:
	MenuState(ChangeableContainer<State>* stateManager, sf::RenderWindow& window, bool& debug);
	MenuState(const Context& context);
	~MenuState();

	void init();
	void processEvents(const sf::Event& ev);
	void updateDebug();
	void update(const sf::Time& dt);
	void renderDebug() const;
	void render() const;
};