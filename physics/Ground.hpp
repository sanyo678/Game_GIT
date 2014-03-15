#pragma once
#include "Box2D/Box2D.h"
#include <list>

class Ground
{

public:
	std::list<b2Vec2>	edges;
	b2Body*				groundBody;
	b2BodyDef			groundBodyDef;
	b2World*			worldPtr;

						Ground(b2Vec2,b2Vec2,b2World*);
	void				makeHole(b2Vec2,float);
	void				build(b2World*);
};

