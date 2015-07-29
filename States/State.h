#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../ChangeableContainer.h"
#include "../ResourceHolder.h"
#include "../SpriteNode.h"
#include "../GUI/Button.h"

class State{
public:
	//CONTEXT
	struct Context{
		sf::RenderWindow& window_;
		ChangeableContainer<State>* stateManager_;
		Context(sf::RenderWindow& window, ChangeableContainer<State>* stateManager)
			:window_(window),
			stateManager_(stateManager){
		}
	};
protected:
	Context context_;
	//bool active_;

	//DRAWABLE STUFF
	//Scene scene_;
	//sf::Font font_;
	sf::Text text_;
	ResourceHolder<sf::Texture> textures_;
	ResourceHolder<sf::Font> fonts_;
	SpriteNode background_;

	//BUTTONS
//private:
//	int pressedButton_;
//	std::vector<GUI::Button> buttons_;
//	std::vector<std::function<void()>> actions_;
//	int action_;
//protected:
//	void createButton(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action);
//	void updateButtons();
//	void pressButton();
//	void registerAction();
//	void performAction();
//	void drawButtons() const;
//	int nButton() const{
//		return pressedButton_;
//	}
//	void doAction(){
//		buttons_.back().action_();
//	}
	///////////////////////////
public:

	State(ChangeableContainer<State>* stateManager, sf::RenderWindow& window/*, bool& debug*/);
	State(const Context& context);
	virtual ~State();

	//void pause(){
	//	active_ = false;
	//}

	virtual void init() = 0;
	virtual void processEvents(const sf::Event& ev) = 0;
	virtual void updateDebug() = 0;
	virtual void update(const sf::Time& dt) = 0;
	virtual void renderDebug() const = 0;
	virtual void render() const = 0;
};

