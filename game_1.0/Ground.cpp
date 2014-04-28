#include "headers.hpp"
//#include <iostream>
//#include <fstream>	 
//#include <math.h>
typedef float positiveAngle;

b2Vec2 rotateVec(b2Vec2, float);
float distance(b2Vec2, b2Vec2);
positiveAngle getPositiveAngle(b2Vec2, b2Vec2);
b2Vec2 getBorder(b2Vec2, b2Vec2, b2Vec2, float);

Ground::Ground(const TextureHolder& textures, b2World* _pWorld, SceneNode* _wreckHolder)
	:SceneNode(_pWorld),
	background(textures.get(Textures::Ground)),
	mTextures(textures),
	mSky(textures.get(Textures::Sky)),
	toReBuild(false),
	wreckHolder(_wreckHolder)
{
	//Box2D part
	std::ifstream F;
	F.open("media\\Maps\\edge1.txt", std::ios::in);
	int x,y;
	while (!F.eof())
	{
		F>>x;
		F>>y;
		edges.push_back(b2Vec2((x*2.44)/SCALE , -(y*2.44)/SCALE + 1000/SCALE + 1726/SCALE));
	}
	F.close();
	edges.push_back(b2Vec2(200,0));
	edges.push_back(b2Vec2(0,0));
	edges.push_back(b2Vec2(*edges.begin()));
	//body init
	groundBodyDef.type = b2_staticBody;
	groundBody = pWorld->CreateBody(&groundBodyDef);
	build(pWorld);
	groundBody -> SetUserData(this);
	//SFML part
	mSky.setPosition(0,-970);
	background.setPosition(0,20);
	/*rTexture.create(9997,1725);
	rTexture.clear(sf::Color::Black);
	rTexture.draw(background);

	for (auto itr = mHoles.begin(); itr != mHoles.end(); ++itr)
	{
		rTexture.draw(itr->sh);
	}

	rTexture.display();
	mSprite = sf::Sprite(rTexture.getTexture());*/
	srand(GetTickCount());
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
		fixtures.push_back( groundBody->CreateFixture(&edgeFixtureDef) );
	}
}

unsigned int Ground::getCategory() const
{
	return Category::Ground;
}

void Ground::makeHole(b2Vec2 epicenter, float radius, point& left, point& right)
{
	std::list<b2Vec2>::iterator first,second, firstToDel, lastToDel, circleStart, circleEnd, itr, leftCircleBorder, rightCircleBorder;
	b2Vec2 leftBorder, rightBorder;
	bool leftFound(false), rightFound(false);

	//find left border
	int numL(0);
	first = this->edges.begin();
	for (second=++(this->edges.begin()); second!=this->edges.end(); first++,second++)
	{
		if (distance(*second, epicenter) <= radius)
		{
			leftBorder = (*first);
			circleStart = first;
			leftFound = true;
			firstToDel = second;
			left = point(numL, circleStart);
			break;
		}
		numL++;
	}

	//find right border
	int numR(0);
	first = --(this->edges.end());
	for (second= --(--this->edges.end()); second!=this->edges.begin(); first--,second--)
	{
		if (distance(*second, epicenter) <= radius)
		{
			rightBorder = (*first);
			circleEnd = first;
			rightFound = true;
			lastToDel = second;
			right = point(numR, circleEnd);
			break;
		}
		numR++;
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

Ground::point::point(int n, std::list<b2Vec2>::iterator i)
	:num(n),
	itr(i)
{
}

Ground::point::point()
{
}

void Ground::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)	  const
{
	//target.draw(mSprite, states);
	
	target.draw(background, states);
	target.draw(mSky, states);
	for (auto i = mHoles.begin(); i != mHoles.end(); i++)
	{
		target.draw(i -> sh, states);
	}
}

void  Ground::makeWrecks()
{
	for (auto itr = newHoles.begin(); itr != newHoles.end(); itr++)
	{
		hole h = *itr;
		for (int i = 0 ; i < h.radius*10; i++)
		{
			std::unique_ptr<Wreck> upWreck(new Wreck(pWorld, h.center, mTextures));
			Wreck* newWreck = upWreck.get();
			newWreck->setPosition(b2ToSfmlVec(h.center).x,b2ToSfmlVec(h.center).y);
			wreckHolder->attachChild(std::move(upWreck));	
		}
	}
	newHoles.clear();
}

void Ground::updateCurrent(sf::Time dt)
{
	if (toReBuild)
	{
		toReBuild = false;
		//build(pWorld);

		std::vector<hole>::iterator itr1, itr2;
		for (itr1 = newHoles.begin(), itr2 = ++newHoles.begin(); itr2 != newHoles.end(); )
		{
			if (distance(itr1->center,itr2->center)<0.1 || itr2->center.y<2)
			{
				itr2 = newHoles.erase(itr2);
			}
			else
			{
				itr1++;
				itr2++;
			}
		}

		if (newHoles.size() == 0)
		{
			return;
		}

		for (auto itr = newHoles.begin(); itr != newHoles.end(); itr++)
		{
			if (itr->center.y<2 || itr->center.x<4 || itr->center.x>195)
				continue;

			point right, left;
			std::list<b2Fixture*>::iterator ir, il, il1, iter;
			int numL, numR;
			makeHole(itr->center, itr->radius, left, right);
			for (il = fixtures.begin(), numL=0; (++numL)!=left.num; il++)
				;
			il1 = il;
			for (ir = --(fixtures.end()), numR=0; (++numR)!=right.num; ir--)
				;
			for (iter = ++il; iter!= ir; )
			{
				groundBody -> DestroyFixture( *iter );
				iter = fixtures.erase(iter);
			}
			//il--;

			std::list<b2Vec2>::iterator first, second;
			++right.itr;  il1++;
			for (first = left.itr, second = ++left.itr; second != right.itr; ++first, ++second)
			{
				b2EdgeShape edgeShape;
				edgeShape.Set( *first, *second );
				b2FixtureDef edgeFixtureDef;
				edgeFixtureDef.shape = &edgeShape;
				fixtures.insert(ir, groundBody->CreateFixture(&edgeFixtureDef) );
			}
		}
		groundBody -> SetUserData(this);

		makeWrecks();
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

Ground::hole::hole(float _rad, b2Vec2 _cent)
			:radius(_rad),
			center(_cent)
{				  
	sh = sf::CircleShape(radius*SCALE,50);
	sh.setOrigin(radius*SCALE,radius*SCALE);
	sh.setFillColor(sf::Color(226,251,252));
	sh.move(b2ToSfmlVec(center).x,b2ToSfmlVec(center).y-1000);
}

void Ground::explosion(b2Vec2 center, float radius)
{
    mHoles.push_back(hole(radius, center));
	newHoles.push_back(hole(radius, center));

	toReBuild = true;

	/*rTexture.clear(sf::Color::Black);
	rTexture.draw(background);

	for (auto itr = mHoles.begin(); itr != mHoles.end(); ++itr)
	{
		rTexture.draw(itr->sh);
	}

	rTexture.display();
	mSprite = sf::Sprite(rTexture.getTexture());*/
}

Ground::~Ground(void)
{
//	pWorld -> DestroyBody(groundBody);
}
