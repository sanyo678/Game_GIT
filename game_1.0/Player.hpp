#pragma once


class Player : public SceneNode
{
public:	
	enum Type       
	{            
		Red,        
		Blue,       
	};

public:
	b2Body*								body;
	int									onFloor;
	bool								isFiring; 
	Command								fireCommand;
	Command								posCommand;
	sf::Sprite							mSprite;
	b2Vec2								firingDirection;
	sf::Vector2f						windowOffset; 
	sf::RenderWindow&					window;
	SceneNode*							projHolder;
	float								countdown;
	Projectile::Type					currentProj;
	std::vector<ProjectileData>			projTable;
	int									hp;
	bool								isHurting;
	float								hurtVel;
	SceneNode*							frontside;
	FontHolder							fonts;
	TextNode*							mHealthDisplay;

										Player(const b2Vec2, const TextureHolder& textures, b2World* _pWorld, sf::RenderWindow&, SceneNode*, SceneNode*);
	virtual void						drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void						updateCurrent(sf::Time);
	virtual unsigned int				getCategory() const;
	void								checkProjectileLaunch(sf::Time, CommandQueue&);
	void								updateFiringDirection();
	void								CreateProjectile(Projectile::Type, b2World*, b2Vec2, const TextureHolder&);
	void								destroyPhysBody();
										~Player();

private:
	b2Vec2								getB2Position();
	Type								mType;
	
};

