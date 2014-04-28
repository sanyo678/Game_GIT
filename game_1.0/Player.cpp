#include "headers.hpp"

Player::Player(const b2Vec2 spawnPos, const TextureHolder& textures, b2World* _pWorld, sf::RenderWindow& _window, SceneNode* _projectiles, SceneNode* _frontside)
	: SceneNode(_pWorld),
	  window(_window),
	  mSprite(textures.get(Textures::Player)), 
	  mType(Red),
	  windowOffset(sf::Vector2f(0.f,0.f)),
	  firingDirection(b2Vec2(0.f,0.f)),
	  isFiring(false) ,
	  projHolder(_projectiles),
	  frontside(_frontside),
	  currentProj(Projectile::Type::Bullet),
	  hp(100),
	  hurtVel(20.0f),
	  isHurting(false)
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
	b2Vec2 pos(0.0f , 1.5f);
	rectShape.SetAsBox(0.5f, 0.5, pos , 0 );
	body->CreateFixture(&boxRectFixtureDef);

	b2FixtureDef boxCircleFixtureDef;
	boxCircleFixtureDef.shape = &circleShape;
	boxCircleFixtureDef.density = 1000;
	boxCircleFixtureDef.friction=3;
	body->CreateFixture(&boxCircleFixtureDef);

	onFloor=0;//сделать false после обработки столкновений
	body->SetUserData( this );

	//SFML part
	projTable = initializeProjectileData();
	countdown = projTable[Projectile::Type::Bullet].countdown;

	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	fonts.load(Fonts::main, "media/Fonts/Washington.ttf");
	std::unique_ptr<TextNode> healthDisplay(new TextNode(pWorld, fonts, ""));
	mHealthDisplay = healthDisplay.get();
	attachChild(std::move(healthDisplay));

	fireCommand.category = Category::Player;
	fireCommand.action = [this, &textures] (SceneNode& node, sf::Time)
	{
		CreateProjectile(currentProj, pWorld, firingDirection, textures);
	};

	posCommand.category = Category::Enemy;
	
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Player::updateCurrent(sf::Time dt)
{
	position = getB2Position();
	setPosition(b2ToSfmlVec(position)-sf::Vector2f(0,0));
	updateFiringDirection();

	mHealthDisplay->setString(std::to_string(hp) + " HP");
	mHealthDisplay->setPosition(-70,-120);

	if (isHurting)
		hp-=hurtVel*dt.asSeconds();
	if (hp<=0)
		isDead = true;

	body -> ApplyLinearImpulse(explosionImpulse, body->GetWorldCenter(), true);
	explosionImpulse = b2Vec2(0,0);
}

void Player::updateFiringDirection()
{
	sf::Vector2i vect = sf::Mouse::getPosition(window);
	sf::Vector2f temp(vect.x - ( 480 + windowOffset.x), -( vect.y - (360 + windowOffset.y)) );
	firingDirection = b2Vec2(temp.x,temp.y);
}

unsigned int Player::getCategory() const 
{  
		return Category::Player;
}

void Player::checkProjectileLaunch(sf::Time dt, CommandQueue& commands)	//p.164
{
	countdown-=dt.asSeconds();
	if (isFiring && countdown<0.0f)
	{
		/*while (commands.mQueue.front().name == "fire")
			commands.pop();*/
		commands.push(fireCommand);
		isFiring = false;
		countdown = projTable[currentProj].countdown;
	}
	
	posCommand.action = [this] (SceneNode& node, sf::Time)
	{
		node.playerPos = this->position; 
	};
	commands.push(posCommand);
}

void Player::CreateProjectile(Projectile::Type type, b2World* pWorld, b2Vec2 dir, const TextureHolder& textures)
{
	std::unique_ptr<Projectile> upProj(new Projectile(type, pWorld, position, dir, textures, frontside));
	Projectile* newProj = upProj.get();
	newProj->setPosition(getPosition().x,getPosition().y);
	projHolder->attachChild(std::move(upProj));	//attach projectile to layer node
}

b2Vec2 Player::getB2Position()
{
	return body->GetPosition();
}

Player::~Player()
{
	pWorld -> DestroyBody(body);
}

 