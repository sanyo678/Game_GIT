#include "headers.hpp"

Wreck::Wreck(b2World* _pWorld, const b2Vec2 spawnPos, const TextureHolder& textures)
	:SceneNode(_pWorld),
	mShape(0.15*SCALE,15)
{
	//Box2D part
	position = spawnPos;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody; 
	bodyDef.position.Set(position.x,position.y); //set the starting position
	bodyDef.angle = 0;
	body = pWorld->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0); //position, relative to body position
	circleShape.m_radius = 0.15;
	b2FixtureDef CircleFixtureDef;
	CircleFixtureDef.shape = &circleShape;
	CircleFixtureDef.density = 1000;
	//CircleFixtureDef.friction=3;
	body->CreateFixture(&CircleFixtureDef);

	//srand(GetTickCount());

	body -> SetUserData(this);
	body->ApplyLinearImpulse( b2Vec2(rand()%2000 - 1000,rand()%2000 - 1000), body->GetWorldCenter(), false );
	lifetime = static_cast<_lifetime>(rand()%16);
	//SFML part
	mShape.setOrigin(0.15*SCALE,0.15*SCALE);
	mShape.setFillColor(sf::Color(211,163,90));
}

void Wreck::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mShape, states);
}

unsigned int  Wreck::getCategory() const
 {
	 return Category::Wreck;
 }

void Wreck::updateCurrent(sf::Time dt)
{
	position = body->GetPosition();
	setPosition(b2ToSfmlVec(position)-sf::Vector2f(0,0));
	t += dt;
	if (lifetime>4 && t.asSeconds() > lifetime)
	{
		isDead = true;
	}

	body -> ApplyLinearImpulse(explosionImpulse, body->GetWorldCenter(), true);
	explosionImpulse = b2Vec2(0,0);
}

Wreck::~Wreck(void)
{
	pWorld -> DestroyBody(body);
}
