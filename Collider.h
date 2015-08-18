#pragma once

#include "Visitor.h"
#include "Entities/Plane.h"
#include "Entities/Mountain.h"
#include "Entities/Mist.h"
#include "Entities/Bonus.h"

struct Collider: public Visitor{
	Plane& plane_;

	Collider(Plane& plane);
	~Collider();
	void visit(Mountain& mountain);
	void visit(Mist& mist);
	void visit(Bonus& bonus);
	void visit(Plane& plane);
};

