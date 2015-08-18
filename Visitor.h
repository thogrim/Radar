#pragma once

class Mountain;
class Mist;
class Bonus;
class Plane;

struct Visitor{
	virtual void visit(Mountain&) = 0;
	virtual void visit(Mist&) = 0;
	virtual void visit(Bonus&) = 0;
	virtual void visit(Plane&) = 0;
};