#pragma once

#include "Visitor.h"
#include "Entities/Plane.h"
#include "Entities/Mountain.h"
#include "Entities/Mist.h"
#include "Entities/Bonus.h"
#include <iostream>

struct Collider: public Visitor{
private:
	bool checkShapeCollision(const sf::ConvexShape& shape);
	bool planeInShape(const sf::ConvexShape& shape, const sf::Vector2f& shapePos);
	Plane& plane_;
public:
	Collider(Plane& plane);
	~Collider();
	void visit(Mountain& mountain);
	void visit(Mist& mist);
	void visit(Bonus& bonus);
	void visit(Plane& plane);
};

