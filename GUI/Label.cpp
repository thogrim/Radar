#include "Label.h"

using namespace GUI;
	
//Label::Label(const sf::Texture& texture, const float posX, const float posY)
//	:Component(texture,posX,posY,1),
//	components_(),
//	pressedComponent_(false){
//}

Label::Label()
	: Component(sf::Texture::Texture(), 0, 0, 1),
	components_(),
	pressedComponent_(false){
}

Label::~Label(){
}

void Label::create(const sf::Texture& texture, const float posX, const float posY){
	sprite_.setTexture(texture);
	textureRect_ = sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y / nSprites_);
	sprite_.setTextureRect(textureRect_);
	///needed?
	setPosition(posX, posY);
}

void Label::createButton(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action){
	CompPtr button(new Button(texture, posX, posY, action, getPosition()));
	components_.push_back(std::move(button));
}

void Label::createCheckbox(const sf::Texture& texture, const float posX, const float posY, const std::function<void()>& action, const std::function<void()>& secondAction){
	CompPtr checkbox(new Checkbox(texture, posX, posY, action, secondAction, getPosition()));
	components_.push_back(std::move(checkbox));
}

bool Label::press(){
	if (hovered_){
		pressed_ = true;
		for (auto& c : components_){
			if (c->press()){
				pressedComponent_ = true;
				return true;
			}
		}
		return false;
	}
	else
		return false;
}

bool Label::release(){
	if (hovered_ && pressedComponent_){
		//looking for pressed component
		auto& found = std::find_if(components_.begin(), components_.end(), 
			[&](CompPtr& c){
			return c->pressed();
		});
		assert(found != components_.end());
		CompPtr& c = *found;
		pressed_ = false;
		pressedComponent_ = false;
		//if presssed component is hovered, register action
		if (c->release()){
			action_ = c->registerAction();
			return true;
		}
		else
			return false;
	}
	else if (hovered_ && !pressedComponent_){
		pressed_ = false;
		return false;
	}
	else if (!hovered_ && pressedComponent_){
		//looking for pressed component
		auto& found = std::find_if(components_.begin(), components_.end(),
			[&](CompPtr& c){
			return c->pressed();
		});
		assert(found != components_.end());
		CompPtr& c = *found;
		//not hovered so no need to check if you should register action
		c->release();
		pressedComponent_ = false;
		pressed_ = false;
		return false;
	}
	else if (!hovered_ && !pressedComponent_){
		pressed_ = false;
		return false;
	}
	else
		return false;
}

const std::function<void()>& Label::registerAction() const{
	return action_;
}

void Label::update(const sf::Vector2i& mousePos){
	if (hoveredNow(mousePos)){
		for (auto& c : components_){
			c->update(mousePos);
		}
	}
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	target.draw(sprite_, states);
	for (auto& c : components_){
		c->draw(target, states);
	}
}