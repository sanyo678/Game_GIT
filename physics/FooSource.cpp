#pragma once
#include <stdlib.h>
#include <math.h>
#include "Box2D/Box2D.h"
#include <list>

typedef float positiveAngle;

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
