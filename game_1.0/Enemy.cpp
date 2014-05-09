#include "headers.hpp"


Enemy::Enemy(b2World* _pworld, b2Vec2 spawnPos, const TextureHolder& textures)
	:SceneNode(_pworld),
	mSprite1r(textures.get(Textures::Enemy1)),
	mSprite1l(textures.get(Textures::Enemy1),sf::IntRect(130,0,-130,122)),
	mSprite2r(textures.get(Textures::Enemy2)),
	mSprite2l(textures.get(Textures::Enemy2),sf::IntRect(130,0,-130,122)),
	countdown(2.0), 
	hp(20),
	firstSprite(true)
{
	//Box2d part
	position = spawnPos;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody; 
	bodyDef.position.Set(position.x,position.y); //set the starting position
	bodyDef.angle = 0;
	body = pWorld->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0); //position, relative to body position
	circleShape.m_radius = 1;
	b2FixtureDef CircleFixtureDef;
	CircleFixtureDef.shape = &circleShape;
	CircleFixtureDef.density = 200;
	body->CreateFixture(&CircleFixtureDef);
	body -> SetUserData(this);
	//SFML part
	sf::FloatRect bounds = mSprite1l.getLocalBounds();
	mSprite1l.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	mSprite1r.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	mSprite2l.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	mSprite2r.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Enemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (firstSprite)
	{
		if(body->GetLinearVelocity().x>0)
			target.draw(mSprite1r, states);
		else 
			target.draw(mSprite1l, states);
	}
	else
	{
		if(body->GetLinearVelocity().x>0)
			target.draw(mSprite2r, states);
		else 
			target.draw(mSprite2l, states);
	}
}

void Enemy::updateCurrent(sf::Time dt)
{
	position = body->GetPosition();
	setPosition(b2ToSfmlVec(position)-sf::Vector2f(0,0));
	if (playerPos.x < position.x)
	{
		b2Vec2 vel = body->GetLinearVelocity();
		float velChange = -7 - vel.x;
		float impulse = body->GetMass() * velChange;
		body->ApplyLinearImpulse( b2Vec2(impulse,0), body->GetWorldCenter(), true );
	}
	else
	{
		b2Vec2 vel = body->GetLinearVelocity();
		float velChange = 7 - vel.x;
		float impulse = body->GetMass() * velChange;
		body->ApplyLinearImpulse( b2Vec2(impulse,0), body->GetWorldCenter(), true );
	}
	spriteCountDown-=dt.asSeconds();
	countdown-=dt.asSeconds();
	if (countdown< 0.0f)
	{
		body -> ApplyLinearImpulse( b2Vec2(0,5000), body->GetWorldCenter(), true );
		countdown = 5.0;
	}

	if (spriteCountDown<=0.0)
	{
		firstSprite = !firstSprite;
		spriteCountDown = 0.3;
	}

	body -> ApplyLinearImpulse(10*explosionImpulse, body->GetWorldCenter(), true);
	explosionImpulse = b2Vec2(0,0);
	if (isDead)
	{
		pWorld -> DestroyBody(body);
	}
}

unsigned int Enemy::getCategory() const
{
	return Category::Enemy;
}

Enemy::~Enemy(void)
{ 
}
