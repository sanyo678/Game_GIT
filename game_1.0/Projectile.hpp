#pragma once

class Projectile : public SceneNode
{
public:
	enum Type
	{
		Bullet = 0,
		Missle,
		TNT,
		TypeCount,

	};
public:
	explicit									Projectile(Type, b2World*, b2Vec2, b2Vec2, const TextureHolder&, SceneNode*);
	virtual unsigned int						getCategory() const;
	float										getDamage() const;
	Type										getType() const;
												~Projectile();

	std::vector<ProjectileData>					Table;
	b2Body*										projBody;
	SceneNode*									expHolder;
	const TextureHolder&						mTextures;
  
private:
	virtual void								updateCurrent(sf::Time dt);
	virtual void								drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Sprite									mSprite;
	Type										mType;
	b2Vec2										mDirection;   
};