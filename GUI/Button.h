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
		//Button(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action, const sf::Vector2f& parentPos);
		//Button(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action, const float parentPosX, const float parentPosY);
		//Button(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action);
		Button();
		~Button();

		void setAction(const std::function<void()>& action);
		bool press();
		bool release();
		const std::function<void()> getAction() const;
		void performAction() const;
		void update(const sf::Vector2i& mousePos);
	};
}