/*
	TODO
	fix the pressedComponent_ management
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Component.h"
#include "Button.h"
#include "Checkbox.h"

namespace GUI{
	class Label: public Component{
	private:
		typedef std::unique_ptr<Component> CompPtr;
		std::vector<CompPtr> components_;
		Component* pressedComponent_;
	public:
		Label();
		~Label();

		//void create(const sf::Texture& texture, const float posX, const float posY);
		//void createButton(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action);
		//void createCheckbox(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action, const std::function<void()>& secondAction);
		void attachComponent(CompPtr component);

		bool press();
		bool release();
		const std::function<void()> getAction() const;
		void performAction() const;
		void update(const sf::Vector2i& mousePos);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}