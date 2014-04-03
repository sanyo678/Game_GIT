#include "headers.hpp"

sf::Vector2f b2ToSfmlVec(b2Vec2 a)
{
	sf::Vector2f b;
	b.x = 20*a.x;
	b.y = 1307 - 20*a.y;
	return b;
}

b2Vec2 SfmlTob2Vec(sf::Vector2f a)
{
	b2Vec2 b;
	b.x = a.x/20.f;
	b.y = (1307 - a.y)/20.f;
	return b;
}