#include "headers.hpp"

SceneNode::SceneNode(b2World* _pWorld)
	: mParent(nullptr),
	pWorld(_pWorld),
	isDead(false),
	explosionImpulse(0,0)
{
}

void SceneNode::attachChild(Ptr child)
{
	child->mParent=this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if( mChildren.begin(), mChildren.end(), [&]
							 (Ptr& p) -> bool { return p.get()==&node; } );

	assert(found!=mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();//комбинация текущей трансформации и новой

	drawCurrent(target, states);

	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		(*itr)->draw(target,states);
	}
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt)
{
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
		(*itr)->update(dt);
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;

	return transform;
}

unsigned int SceneNode::getCategory() const
{   
	return Category::Scene;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{ 
	if (command.category & getCategory())     
		command.action(*this, dt);

	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
		(*itr)->onCommand(command,dt);
}

bool SceneNode::isToKill()	 const
{
	return isDead;
}

void SceneNode::removeDead()
{
	auto deadFieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isToKill));
	mChildren.erase(deadFieldBegin, mChildren.end());

	std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeDead));
}

