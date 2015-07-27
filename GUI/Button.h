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
			NORMAL=1,
			HOVERED=2,
			PRESSED=3
		};

		//COMPONENT///////////
		//bool hovered_;
		//bool pressed_;
		//sf::Sprite sprite_;
		//const int nSprites_;
		//const sf::IntRect textureRect_;
		//std::function<void()> func_;
		//void setSprite(const int nSprite){
		//	assert(nSprite <= nSprites_ && nSprite > 0);
		//	sprite_.setTextureRect(sf::IntRect(0, (nSprite - 1)*textureRect_.height, textureRect_.width, textureRect_.height));
		//}

		//void hoveredNow(const sf::Vector2i& mousePos);
		///////////////////////

	public:
		std::function<void()> action_;
		Button(const sf::Texture& texture, const float posX, const float posY);
		//Button();
		~Button();

		//bool performAction(){
		//	if (hovered_){
		//		//action_();
		//		pressed_ = false;
		//		return true;
		//	}
		//	else
		//		return false;
		//}

		//void processEvents(const sf::Event& ev);

		bool press(){
			if (hovered_){
				pressed_ = true;
				setSprite(Sprite::PRESSED);
				return true;
			}
			else
				return false;
		}

		//void setAction(const std::function<void()>& action){
		//	action_ = action;
		//}

		void update(const sf::Vector2i& mousePos);

		/*void doAction(){
			action_();
		}*/

		//component
		//void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	};
}