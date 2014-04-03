#pragma once

class Projectile : public SceneNode
{
public:
	enum Type
	{
		Bullet = 0,
		Rocket,
		TNT,
		TypeCount,

	};
public:
  explicit				 Projectile(Type, const TextureHolder&, float, b2World*);

  virtual unsigned int   getCategory()           const;
  float                  getDamage()             const;
  float                  getAngle()              const;
  sf::Vector2f           getStartVelocity()      const;
  void				     Fire();

  const std::vector<ProjectileData>				Table;
  
private:
  virtual void           UpdateCurrent(sf::Time dt, CommandQueue& command);
  virtual void	         drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	sf::Sprite								mSprite;
	Type									mType;
	float									Angle;        //значение угла под которым вылетает снар€д. Ќужно дл€ Box2d 
};