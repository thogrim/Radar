#pragma once

#include <SFML/Graphics.hpp>
#include <stack>
#include <memory>
#include "States/State.h"
#include "States/TitleState.h"
#include "States/MenuState.h"
#include "ChangeableContainer.h"

class StateManager: public ChangeableContainer<State>
{
private:
	//STATE STACK
	std::stack<std::unique_ptr<State>> stateStack_;

	//PENDING CHANGE TO STACK
	struct PendingChange{
		Action action_;
		State* state_;
		PendingChange(Action action, State* state)
			:action_(action),
			state_(state){
		}
	} pendingChange_;

	bool changeRequested(){
		return pendingChange_.action_ != Action::NONE;
	}

	void resetChange(){
		pendingChange_.action_ = Action::NONE;
		pendingChange_.state_ = nullptr;
	}
public:
	//CONSTRUCTORS AND DESTRUCTOR
	StateManager();
	virtual ~StateManager();

	//State* peek(){
	//	if (stateStack_.empty())
	//		return nullptr;
	//	return stateStack_.top().get();
	//}

	void pendChange(Action action, State* state);
	void processEvents(const sf::Event& ev);
	void update(const sf::Time& dt);
	sf::Text getDrawable() const;
};

