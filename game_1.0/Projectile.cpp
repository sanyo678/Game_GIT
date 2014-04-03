#include "headers.hpp"


Projectile::Projectile(Type type, const TextureHolder& texture, float _angle, b2World* _pWorld):
	SceneNode(_pWorld),
	mType(type), 
	Angle(_angle),
	mSprite(texture.get(Table[type].texture))	
{
	//Box2D part

	//SFML part
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

unsigned int Projectile::getCategory() const
{
	return Category::Type::Projectile;
}

 float Projectile::getDamage() const
 {
	 return Table[mType].Damage;
 }

 sf::Vector2f    Projectile::getStartVelocity() const
 {
	 return Table[mType].StartVelocity;
 }

 float Projectile::getAngle() const
 {
	 return Angle;
 }

 void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
 {
	 target.draw(mSprite, states);
 }

 void Projectile::UpdateCurrent(sf::Time dt, CommandQueue& command)
 {

 }

 void Projectile::Fire()
 {
	/*sf::Vector2i vect = sf::Mouse::getPosition(this->mWindow);		
    sf::Transform transform = this->getWorldTransform();
	sf::Vector2f  ProjPosition = transform.transformPoint(0,0);
	sf::Vector2f temp(vect.x-ProjPosition.x, ProjPosition.y-vect.y);
	 this->Angle=atan(temp.y/temp.x);	*/  
 }