#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <assert.h>
#include "Component.h"

namespace GUI{
	class Button :public Component{
	private:
		enum Sprite{
			NORMAL = 1,
			HOVERED = 2,
			PRESSED = 3
		};

		std::function<void()> action_;
	public:
		Button();
		~Button();

		void setAction(const std::function<void()>& action);
		//void setText(const sf::Text& text);
		bool press();
		bool release();
		const std::function<void()> getAction() const;
		void performAction() const;
		void update(const sf::Vector2i& mousePos);
	};
}