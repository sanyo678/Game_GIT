#include "headers.hpp"
//#include "SFML/System.hpp"

//#include <iostream>

Player::Player(const b2Vec2 spawnPos, const TextureHolder& textures, b2World* _pWorld, sf::RenderWindow& _window)
	: SceneNode(_pWorld),
	  window(_window),
	  mSprite(textures.get(Textures::Player)), 
	  mType(Red),
	  windowOffset(sf::Vector2f(0.f,0.f)),
	  firingDirection(b2Vec2(0.f,0.f)),
	  isFiring(false)
{
	//Box2D part
	position = spawnPos;
	b2BodyDef boxBodyDef;
	boxBodyDef.type = b2_dynamicBody; 
	boxBodyDef.position.Set(position.x,position.y); //set the starting position
	boxBodyDef.angle = 0;
	body = pWorld->CreateBody(&boxBodyDef);
	body->SetFixedRotation(true);
		
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0); //position, relative to body position
	circleShape.m_radius = 1; 
  	b2PolygonShape rectShape;
	b2FixtureDef boxRectFixtureDef;
	boxRectFixtureDef.shape = &rectShape;
	boxRectFixtureDef.density = 1000;
	b2Vec2 pos(0.0f , 2.0f);
	rectShape.SetAsBox(0.5f, 1, pos , 0 );
	body->CreateFixture(&boxRectFixtureDef);

	b2FixtureDef boxCircleFixtureDef;
	boxCircleFixtureDef.shape = &circleShape;
	boxCircleFixtureDef.density = 1;
	boxCircleFixtureDef.friction=3;
	body->CreateFixture(&boxCircleFixtureDef);

	onFloor=true;//сделать false после обработки столкновений
	body->SetUserData( this );

	//SFML part
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	fireCommand.category = Category::RedPlayer;
	fireCommand.action = [this, &textures] (SceneNode& node, sf::Time)
	{
		//CreateProjectile(node, Projectile::Type::Rocket, firingDirection);
	};
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Player::updateCurrent(sf::Time dt)
{
	position = getB2Position();
	setPosition(b2ToSfmlVec(position)-sf::Vector2f(0,50));
	updateFiringDirection();
}

void Player::updateFiringDirection()
{
	sf::Vector2i vect = sf::Mouse::getPosition(window);
	sf::Vector2f temp(vect.x - ( 400 + windowOffset.x), -( vect.y - (300 + windowOffset.y)) );
	firingDirection = b2Vec2(temp.x,temp.y);
}

unsigned int Player::getCategory() const 
{
	switch (mType) 
	{       
	case Red:  
		return Category::RedPlayer;
	default: 
		return Category::BluePlayer; 
	} 
}

void Player::checkProjectileLaunch(sf::Time dt, CommandQueue& commands)	//p.164
{
	if (isFiring)
	{
		commands.push(fireCommand);
		isFiring = false;
	}
}

b2Vec2 Player::getB2Position()
{
	return body->GetPosition();
}

 