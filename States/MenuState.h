#pragma once

#include "State.h"
#include "TitleState.h"
#include "GameplayState.h"
#include "../ChangeableContainer.h"
//#include "../GUI/Component.h"
#include "../GUI/Label.h"
#include "../Entities/Plane.h"

class MenuState : public State{
private:
	GUI::Label label_;
	//GUI::Button button_;
	//Plane plane_;
	//Entity entity_;
	//std::vector<std::unique_ptr<Entity>> planes_;
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