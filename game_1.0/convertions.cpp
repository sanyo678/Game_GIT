#include "headers.hpp"

sf::Vector2f b2ToSfmlVec(b2Vec2 a)
{
	sf::Vector2f b;
	b.x = SCALE*a.x;
	b.y = 3726 - SCALE*a.y;
	return b;
}

b2Vec2 SfmlTob2Vec(sf::Vector2f a)
{
	b2Vec2 b;
	b.x = a.x/SCALE;
	b.y = (3726 - a.y)/SCALE;
	return b;
}

float length(b2Vec2 a)
{
	return sqrt(a.x*a.x + a.y*a.y);
}