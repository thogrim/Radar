#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <assert.h>
#include "Component.h"
//#include "SpriteNode.h"
//#include "Selectable.h"

namespace GUI{
	class Button :public Component{
	private:
		enum Sprite{
			NORMAL = 1,
			HOVERED = 2,
			PRESSED = 3
		};
	public:
		Button(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action, const sf::Vector2f& parentPos);
		Button(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action, const float parentPosX, const float parentPosY);
		Button(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action);
		~Button();
		bool press();
		bool release();
		const std::function<void()>& registerAction() const;
		void update(const sf::Vector2i& mousePos);
	};
}