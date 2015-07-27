#pragma once

#include "State.h"
#include "TitleState.h"
#include "../ChangeableContainer.h"
#include "../GUI/Button.h"
#include "../Entities/Entity.h"

class MenuState : public State{
//private:
	//std::vector<GUI::Button> buttons_;
public:
	MenuState(ChangeableContainer<State>* stateManager, sf::RenderWindow& window);
	MenuState(const Context& context);
	~MenuState();

	void init();
	void processEvents(const sf::Event& ev);
	void updateDebug();
	void update(const sf::Time& dt);
	void renderDebug() const;
	void render() const;
};