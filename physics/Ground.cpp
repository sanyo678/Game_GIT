#pragma once
#include "Ground.hpp"

typedef float positiveAngle;

b2Vec2 rotateVec(b2Vec2, float);
float distance(b2Vec2, b2Vec2);
positiveAngle getPositiveAngle(b2Vec2, b2Vec2);
b2Vec2 getBorder(b2Vec2, b2Vec2, b2Vec2, float);


Ground::Ground(b2Vec2 begin,b2Vec2 end,b2World* world)
{
	//fill the edges list
	edges.push_front(begin);
	edges.push_back(end);
	//body init
	groundBodyDef.type = b2_staticBody;
	groundBody = world->CreateBody(&groundBodyDef);
	//add fixture
	b2EdgeShape edgeShape;
	edgeShape.Set( begin, end );
	b2FixtureDef edgeFixtureDef;
	edgeFixtureDef.shape = &edgeShape;
	groundBody->CreateFixture(&edgeFixtureDef);
}

void Ground::build(b2World* world)
{
	world->DestroyBody(groundBody);
	groundBody = world->CreateBody(&groundBodyDef);

	std::list<b2Vec2>::iterator first,second;
	first=edges.begin();
	for (second = ++(edges.begin()); second != edges.end(); first++,second++)
	{
		b2EdgeShape edgeShape;
		edgeShape.Set( *first, *second );
		b2FixtureDef edgeFixtureDef;
		edgeFixtureDef.shape = &edgeShape;
		groundBody->CreateFixture(&edgeFixtureDef);
	}
}

void Ground::makeHole(b2Vec2 epicenter, float radius)
{
	std::list<b2Vec2>::iterator first,second, firstToDel, lastToDel, circleStart, circleEnd, itr, leftCircleBorder, rightCircleBorder;
	b2Vec2 leftBorder, rightBorder;
	bool leftFound(false), rightFound(false);

	//find left border
	first = this->edges.begin();
	for (second=++(this->edges.begin()); second!=this->edges.end(); first++,second++)
	{
		if (distance(*second, epicenter) <= radius)
		{
			leftBorder = (*first);
			circleStart = first;
			leftFound = true;
			firstToDel = second;
			break;
		}
	}

	//find right border
	first = --(this->edges.end());
	for (second= --(--this->edges.end()); second!=this->edges.begin(); first--,second--)
	{
		if (distance(*second, epicenter) <= radius)
		{
			rightBorder = (*first);
			circleEnd = first;
			rightFound = true;
			lastToDel = second;
			break;
		}
	}

	if ( !(leftFound && rightFound) )
		return;

	leftBorder = getBorder(*circleStart, *firstToDel, epicenter, radius);
	leftCircleBorder = circleStart;
	leftCircleBorder++;
	this->edges.insert(leftCircleBorder,leftBorder);
	leftCircleBorder--;
	

	rightBorder = getBorder(*circleEnd, *lastToDel, epicenter, radius);
	rightCircleBorder = circleEnd;
	this->edges.insert(rightCircleBorder,rightBorder);
	rightCircleBorder--;

	this->edges.erase(firstToDel, ++lastToDel);

	b2Vec2 aVec(leftBorder.x-epicenter.x, leftBorder.y-epicenter.y), bVec(rightBorder.x-epicenter.x, rightBorder.y-epicenter.y);
	positiveAngle ab = getPositiveAngle(aVec,bVec);

	positiveAngle step = 1/57.296;

	b2Vec2 toInsert = rotateVec(aVec, step);
	positiveAngle rotated(step);
	for (itr = ++leftCircleBorder; rotated < ab; rotated+=step)
	{
		this->edges.insert(itr,epicenter + toInsert);
		toInsert = rotateVec(toInsert,step);
	}
}

b2Vec2 getBorder(b2Vec2 a, b2Vec2 b, b2Vec2 o, float r)
{
	float AO(sqrt((a.x-o.x)*(a.x-o.x) + (a.y-o.y)*(a.y-o.y)));
	float AB(sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)));
	float BO(sqrt((b.x-o.x)*(b.x-o.x) + (b.y-o.y)*(b.y-o.y)));

	float cosA = (AO*AO + AB*AB - BO*BO)/(2 * AO * AB);
	float sinA = sqrt(1 - cosA*cosA);
	float beta = asin(AO/r*sinA);
	float gamma = b2_pi - asin(sinA) - beta;

	float AC = sqrt( AO*AO + r*r - 2 * AO * r );

	b2Vec2 ans;
	ans = a + (AC/AB)*(b-a);

	return ans;
}

