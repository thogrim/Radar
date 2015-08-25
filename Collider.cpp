#include "Collider.h"

Collider::Collider(Plane& plane)
	:plane_(plane){
}

Collider::~Collider(){
}

bool Collider::checkShapeCollision(const sf::ConvexShape& shape){
	sf::Vector2f pos(plane_.getPosition());
	sf::Vector2f p0;
	sf::Vector2f p1;
	unsigned int i = 0;
	float a, b, c, cosTheta, area;
	while (i < shape.getPointCount()-1){
		p0 = shape.getPoint(i);
		p1 = shape.getPoint(i+1);
		++i;
		a = sqrt(pow(pos.x - p0.x, 2) + pow(pos.y - p0.y, 2));
		b = sqrt(pow(pos.x - p1.x, 2) + pow(pos.y - p1.y, 2));
		c = sqrt(pow(p0.x - p1.x, 2) + pow(p0.y - p1.y, 2));
		if (a > b){
			cosTheta = ((pos.x - p1.x)*(p0.x - p1.x) + (pos.y - p1.y)*(p0.y - p1.y)) / (b*c);
			if (cosTheta < 0 && b < plane_.getHitboxRadius())
				return true;
		}
		else{
			cosTheta = ((pos.x - p0.x)*(p1.x - p0.x) + (pos.y - p0.y)*(p1.y - p0.y)) / (a*c);
			if (cosTheta < 0 && a < plane_.getHitboxRadius())
				return true;
		}
		if (cosTheta>=0){
			area = (p0.x - pos.x)*(p1.y - pos.y) - (p0.y - pos.y)*(p1.x - pos.x);
			if (abs(area) < c*plane_.getHitboxRadius())
				return true;
		}
	}
	//checking collision for last wall
	p0 = shape.getPoint(i);
	p1 = shape.getPoint(0);
	a = sqrt(pow(pos.x - p0.x, 2) + pow(pos.y - p0.y, 2));
	b = sqrt(pow(pos.x - p1.x, 2) + pow(pos.y - p1.y, 2));
	c = sqrt(pow(p0.x - p1.x, 2) + pow(p0.y - p1.y, 2));
	if (a > b){
		cosTheta = ((pos.x - p1.x)*(p0.x - p1.x) + (pos.y - p1.y)*(p0.y - p1.y)) / (b*c);
		if (cosTheta < 0 && b < plane_.getHitboxRadius())
			return true;
	}
	else{
		cosTheta = ((pos.x - p0.x)*(p1.x - p0.x) + (pos.y - p0.y)*(p1.y - p0.y)) / (a*c);
		if (cosTheta < 0 && a < plane_.getHitboxRadius())
			return true;
	}
	if (cosTheta >= 0){
		area = (p0.x - pos.x)*(p1.y - pos.y) - (p0.y - pos.y)*(p1.x - pos.x);
		if (abs(area) < c*plane_.getHitboxRadius())
			return true;
	}
	return false;
}

bool Collider::planeInShape(const sf::ConvexShape& shape, const sf::Vector2f& shapePos){
	sf::Vector2f pos(plane_.getPosition());
	sf::Vector2f p0;
	sf::Vector2f p1;
	unsigned int i = 0;
	float a, b, c;
	while (i < shape.getPointCount() - 1){
		p0 = shape.getPoint(i) + shapePos;
		p1 = shape.getPoint(i + 1) + shapePos;
		++i;
		a = p0.y - p1.y;
		b = p1.x - p0.x;
		c = p1.y*p0.x - p1.x*p0.y;
		if (a*pos.x + b*pos.y + c < 0)
			return false;

	}
	//checking last wall
	p0 = shape.getPoint(i) + shapePos;
	p1 = shape.getPoint(0) + shapePos;
	a = p0.y - p1.y;
	b = p1.x - p0.x;
	c = p1.y*p0.x - p1.x*p0.y;
	if (a*pos.x + b*pos.y + c < 0)
		return false;
	return true;
}

void Collider::visit(Mountain& mountain){
	float hitbox = plane_.getHitboxRadius();
	sf::FloatRect bounds(mountain.getBounds());
	bounds.left -= hitbox;
	bounds.top -= hitbox;
	bounds.width += 2 * hitbox;
	bounds.height += 2 * hitbox;
	//if plane is not in bounds then return
	if (bounds.contains(plane_.getPosition()))
		if (checkShapeCollision(mountain.getShape())){
			//plane_.rotate(180);
			//plane_.setPosition(200.f, 200.f);
			plane_.destroy();

		}
}

void Collider::visit(Mist& mist){
	sf::FloatRect bounds(mist.getBounds());
	bounds.left += mist.getPosition().x;
	bounds.top += mist.getPosition().y;
	if (bounds.contains(plane_.getPosition())){
		if (planeInShape(mist.getShape(), mist.getPosition()))
			plane_.setVisibility(false);
		else
			plane_.setVisibility(true);
	}
	else
		plane_.setVisibility(true);
}

void Collider::visit(Bonus& bonus){
	sf::Vector2f ppos(plane_.getPosition());
	sf::Vector2f bpos(bonus.getPosition());
	if (sqrt(pow(ppos.x - bpos.x, 2) + pow(ppos.y - bpos.y, 2)) < plane_.getHitboxRadius()){
		plane_.collectPoints(bonus.getScore());
		bonus.destroy();
	}
}

void Collider::visit(Plane& plane){

}
//void Collider::collider