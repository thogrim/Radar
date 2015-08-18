#include "Collider.h"

Collider::Collider(Plane& plane)
	:plane_(plane){
}

Collider::~Collider(){
}

void Collider::visit(Mountain& mountain){
	if (mountain.getBounds().contains(plane_.getPosition()))
		plane_.setVelocity(0,0);
}

void Collider::visit(Mist& mist){
	if (mist.getBounds().contains(plane_.getPosition()))
		plane_.setVelocity(0, 0);
}

void Collider::visit(Bonus& bonus){

}

void Collider::visit(Plane& bonus){

}
//void Collider::collider