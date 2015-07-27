#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>

namespace GUI{
	class Component: public sf::Drawable, sf::Transformable{
	protected:
		bool hovered_;
		bool pressed_;
		sf::Sprite sprite_;
		const int nSprites_;
		const sf::IntRect textureRect_;

		void setSprite(const int nSprite){
			assert(nSprite <= nSprites_ && nSprite > 0);
			sprite_.setTextureRect(sf::IntRect(0, (nSprite-1)*textureRect_.height,textureRect_.width,textureRect_.height));
		}
		void hoveredNow(const sf::Vector2i& mousePos);
	public:
		Component(const sf::Texture& texture, const float posX, const float posY, const int nSprites);
		//Component();
		virtual ~Component();

		bool hovered() const{
			return hovered_;
		}

		bool pressed() const{
			return pressed_;
		}

		void release(){
			pressed_ = false;
		}

		//virtual void processEvents(const sf::Event& ev) = 0;
		virtual bool press() = 0;
		virtual void update(const sf::Vector2i& mousePos) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}