#pragma once

#include "Component.h"

namespace GUI{
	class Checkbox: public Component{
	private:
		enum Sprite{
			NOT_TOGGLED = 1,
			TOGGLED = 2,
			HOVERED_NOT_TOGGLED = 3,
			HOVERED_TOGGLED = 4,
			PRESSED_NOT_TOGGLED = 5,
			PRESSED_TOGGLED = 6
		};
		bool toggled_;
		std::function<void()> toggleAction_;
		std::function<void()> untoggleAction_;
	public:
		//Checkbox(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action, const std::function<void()>& secondAction, const sf::Vector2f& parentPos);
		//Checkbox(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action, const std::function<void()>& secondAction, const float parentPosX, const float parentPosY);
		//Checkbox(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action, const std::function<void()>& secondAction);
		Checkbox();
		~Checkbox();

		void setToggleAction(const std::function<void()>& action);
		void setUntoggleAction(const std::function<void()>& action);
		bool press();
		bool release();
		const std::function<void()> getAction() const;
		void performAction() const;
		void update(const sf::Vector2i& mousePos);
	};
}