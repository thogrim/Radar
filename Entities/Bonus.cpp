#include "Bonus.h"

//Bonus::Bonus(const sf::Texture& texture, int score)
//	:SpriteEntity(),
//	score_(),
//	lifetime_(sf::Time::Zero){
//	setTexture(texture);
//	setScore
//}

Bonus::Bonus(const sf::Texture& texture, const sf::Font& font)
	: SpriteEntity(), 
	score_(),
	lifetime_(sf::Time::Zero){
	setTexture(texture);
	centerOrigin();
	score_.setFont(font);
	score_.setCharacterSize(16);
	//score_.setColor
}

Bonus::~Bonus(){
}

void Bonus::setScore(int score){
	score_.setString(std::to_string(score));
	float xoffset = score_.getLocalBounds().width/2;
	float yoffset = score_.getCharacterSize()*5/8;
	score_.setOrigin(xoffset+1,yoffset+1);
}

void Bonus::setLifetime(float lifetime){
	lifetime_ = sf::seconds(lifetime);
}

int Bonus::getScore() const{
	return std::stoi(static_cast<std::string>(score_.getString()));
}

void Bonus::update(const sf::Time& dt){
	//do nothing
}

void Bonus::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	target.draw(sprite_, states);
	target.draw(score_, states);
}

void Bonus::accept(Visitor& c){
	c.visit(*this);
}