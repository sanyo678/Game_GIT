#pragma once
#include "SFML/System.hpp"
#include "SceneNode.hpp"
#include "Box2D/Box2D.h"

class Entity : public SceneNode
{
public:
	void			setVelocity(sf::Vector2f velocity);
	void			setVelocity(double vx, double vy);
	sf::Vector2f	getVelocity() const;
	b2Body			body;
	b2BodyDef		bodyDef;



private:
	virtual void	updateCurrent(sf::Time dt);

private:
	sf::Vector2f	mVelocity;
};

