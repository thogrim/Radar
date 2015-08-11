#include "SceneNode.h"

SceneNode::SceneNode()
	:parent_(nullptr),
	children_(){
}

//SceneNode::SceneNode(const SceneNode& node)
//	:parent_(node.parent_),
//	children_(){
//}

SceneNode::~SceneNode(){
}

void SceneNode::attachChild(ScenePtr child){
	child->parent_ = this;
	children_.push_back(std::move(child));
}

SceneNode::ScenePtr SceneNode::detachChild(const SceneNode& child){
	auto found = std::find_if(children_.begin(), children_.end(),
		[&](ScenePtr& p){
		return p.get() == &child; 
	});
	assert(found != children_.end());
	ScenePtr result = std::move(*found);
	result->parent_ = nullptr;
	children_.erase(found);
	return result;
}

void SceneNode::updateCurrent(const sf::Time& dt){
	//do nothing
}

void SceneNode::update(const sf::Time& dt){
	updateCurrent(dt);
	for (const ScenePtr& ch : children_){
		ch->update(dt);
	}
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
	//do nothing
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	drawCurrent(target, states);
	for (const ScenePtr& ch : children_)
		ch->draw(target, states);
}

sf::Transform SceneNode::getWorldTransform(){
	sf::Transform worldTransform = getTransform();
	for (const SceneNode* node = parent_; node != nullptr; node = node->parent_){
		worldTransform *= node->getTransform();
	}
	return worldTransform;
}

sf::Vector2f SceneNode::getWorldPosition(){
	return getWorldTransform()*sf::Vector2f();
}