#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>
#include <functional>

namespace GUI{
	class Component: public sf::Drawable, public sf::Transformable{
	protected:
		bool hovered_;
		bool pressed_;
		sf::Sprite sprite_;
		const int nSprites_;
		sf::IntRect textureRect_;
		std::function<void()> action_;
		sf::Vector2f parentPos_;

		void setSprite(const int nSprite){
			assert(nSprite <= nSprites_ && nSprite > 0);
			sprite_.setTextureRect(sf::IntRect(0, (nSprite-1)*textureRect_.height,textureRect_.width,textureRect_.height));
		}

		bool hoveredNow(const sf::Vector2i& mousePos);
		
		Component(const sf::Texture& texture, const float posX, const float posY, const int nSprites, const std::function<void()>& action, sf::Vector2f parentPos);
		Component(const sf::Texture& texture, const float posX, const float posY, const int nSprites, const std::function<void()>& action, const float parentPosX, const float parentPosY);
	public:
		Component(const sf::Texture& texture, const float posX, const float posY, const int nSprites);
		virtual ~Component();

		bool hovered() const{
			return hovered_;
		}

		bool pressed() const{
			return pressed_;
		}

		virtual bool press() = 0;
		virtual bool release() = 0;
		virtual const std::function<void()>& registerAction() const = 0;
		virtual void update(const sf::Vector2i& mousePos) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}