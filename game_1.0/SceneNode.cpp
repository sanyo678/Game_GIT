#pragma once
#include "SceneNode.hpp"
#include <algorithm> //find_if
#include "assert.h"  //assert()
#include "Command.hpp"

SceneNode::SceneNode()
	: mParent(nullptr)
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

