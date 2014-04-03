#include "headers.hpp"
//#include <iostream>
//#include <fstream>	 
//#include <math.h>
typedef float positiveAngle;

b2Vec2 rotateVec(b2Vec2, float);
float distance(b2Vec2, b2Vec2);
positiveAngle getPositiveAngle(b2Vec2, b2Vec2);
b2Vec2 getBorder(b2Vec2, b2Vec2, b2Vec2, float);

Ground::Ground(const TextureHolder& textures, b2World* _pWorld)
	:SceneNode(_pWorld),
	mSprite(textures.get(Textures::Ground))
{
	//Box2D part
	std::ifstream F;
	F.open("C:\\Users\\Acer\\Desktop\\Универ\\2 семестр\\groundTest\\groundTest\\edge1.txt", std::ios::in);
	int x,y;
	while (!F.eof())
	{
		F>>x;
		F>>y;
		edges.push_back(b2Vec2(x/20.f , -y/20.f + 300/20 + 707/20));
	}
	F.close();
	//body init
	groundBodyDef.type = b2_staticBody;
	groundBody = pWorld->CreateBody(&groundBodyDef);
	build(pWorld);
	//SFML part
	//mSprite.setPosition(0.0f,300.0f);
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

void Ground::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Ground::updateCurrent(sf::Time dt)
{
}

Ground::~Ground(void)
{
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

positiveAngle getPositiveAngle(b2Vec2 a, b2Vec2 b)
{
	positiveAngle ax, xb;
	if (a.x >= 0)
	{
		if (a.y >= 0)
		{ax = 2* b2_pi - atan(a.y / a.x);}
		else
		{ax = abs(atan(a.y / a.x));}
	} else
	{
		if (a.y >= 0)
		{ax = b2_pi + abs(atan(a.y / a.x));}
		else
		{ax = b2_pi - atan(a.y / a.x);}
	}

	if (b.x >= 0)
	{
		if (b.y >= 0)
		{xb = atan(b.y / b.x);}
		else
		{xb = 2*b2_pi - abs(atan(b.y / b.x));}
	} else
	{
		if (b.y >= 0)
		{xb = b2_pi - abs(atan(b.y / b.x));}
		else
		{xb = b2_pi + abs(atan(b.y / b.x));}
	}
	positiveAngle ans = ax+xb;
	while (ans>=2*b2_pi)
		ans-=2*b2_pi;
	while (ans<=-2*b2_pi)
		ans+=2*b2_pi;
	return ans;
}

float distance(b2Vec2 a, b2Vec2 b)
{
	return sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) );
}

b2Vec2 rotateVec(b2Vec2 vec, float angle)
{
	b2Vec2 ans;
	ans.x = vec.x*cos(angle) - vec.y*sin(angle);
	ans.y = vec.x*sin(angle) + vec.y*cos(angle);
	return ans;
}

