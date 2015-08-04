/*
	TODO:
	in setDestination method check if it is possible to reach destination
	change selection sprite to primitive
*/
#pragma once

#include "Entity.h"
#include "Selectable.h"
#include <iostream>

const float PI = 3.14159265f;

class Plane: public Entity, public Selectable{
private:
	/*
		Plane's velocity and acceleration values
		are in polar coordinate system!
	*/
	bool hovered_;
	bool selected_;
	bool hasDestination_;
	sf::Vector2f destination_;
	//float toRotate;

	sf::IntRect hoveredRect_;
	sf::IntRect selectedRect_;
	sf::Sprite selectionSprite_;

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	float countAngleDifferrence();
public:
	Plane(const sf::Texture& texture, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, const sf::Vector2f& maxVelocity, const sf::Vector2f& accValues);
	Plane(const sf::Texture& texture, const float vx, const float vy, const float ax, const float ay, const float maxVx, const float maxVy, const float accValueX, const float accValueY);
	Plane();
	~Plane();

	void setSelectionTexture(const sf::Texture& texture){
		selectionSprite_.setTexture(texture);
		selectionSprite_.setTextureRect(sf::IntRect(0, 0, 0, 0));
		selectionSprite_.setOrigin(texture.getSize().x/2, texture.getSize().y / 4);
		hoveredRect_= sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y/2);
		selectedRect_ = sf::IntRect(0, texture.getSize().y / 2, texture.getSize().x, texture.getSize().y / 2);
	}

	bool selected() const{
		return selected_;
	}

	bool hovered() const{
		return  hovered_;
	}

	/*void printInfo(){
		std::cout << "global bounds:\nwidth: " << sprite_.getGlobalBounds().width
			<< "\nheight: " << sprite_.getGlobalBounds().height
			<< "\ntop: " << sprite_.getGlobalBounds().top
			<< "\nleft: " << sprite_.getGlobalBounds().left
			<< std::endl;
	}*/
	bool hover(const sf::Vector2i& mousePos);
	bool select();
	bool unselect();
	void setDestination(const sf::Vector2i& destination);
	void update(const sf::Time& dt);
};