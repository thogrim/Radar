#pragma once

#include "SpriteEntity.h"

class Bonus: public SpriteEntity{
private:
	sf::Text score_;
	sf::Time lifetime_;
public:
	//Bonus(const sf::Texture& texture, int score);
	Bonus(const sf::Texture& texture, const sf::Font& font);
	~Bonus();

	void setScore(int score);
	void setLifetime(float lifetime);
	int getScore() const;

	void update(const sf::Time& dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void accept(Visitor& c);
};

