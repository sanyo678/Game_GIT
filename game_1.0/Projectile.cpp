#include "headers.hpp"


Projectile::Projectile(Type type, b2World* _pWorld, b2Vec2 pos, b2Vec2 dir, const TextureHolder& textures, SceneNode* _expH):
	SceneNode(_pWorld),
	expHolder(_expH),
	Table(initializeProjectileData()),
	mType(type), 
	mDirection(dir),
	mSprite(textures.get(Table[type].texture)),
	mTextures(textures)
{
	//Box2D part
	Table[type].buildBody(*this, pos, dir);
	projBody -> SetUserData(this);
	projBody->ApplyLinearImpulse( Table[mType].StartVelocity*dir, projBody->GetWorldCenter(), true );
	//SFML part
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width - 3, bounds.height / 2.f);
}

 float Projectile::getDamage() const
 {
	 return Table[mType].Damage;
 }

 Projectile::Type Projectile::getType() const
 {
	 return mType;
 }


 unsigned int Projectile::getCategory() const
 {
	 return Category::Projectile;
 }

 void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
 {
	 target.draw(mSprite, states);
 }

 void Projectile::updateCurrent(sf::Time dt)
 {
	typedef float positiveAngle;
	positiveAngle getPositiveAngle(b2Vec2 a, b2Vec2 b);	

	 //remove this to child class
	b2Vec2 missleVel = projBody->GetLinearVelocity();
		float a = projBody->GetAngle();
		if (missleVel.x != 0 || missleVel.y !=0)
		{
			float dPhi = getPositiveAngle(b2Vec2(1,0), missleVel);
			projBody->SetTransform(projBody->GetPosition(), dPhi - b2_pi/2);
			a = projBody->GetAngle();

		}
	//------------
	position = projBody->GetPosition();
	setPosition(b2ToSfmlVec(position)-sf::Vector2f(0,0));
	rotation = projBody->GetAngle() - b2_pi/2;
	setRotation(180 - (rotation)*57.7);

	if (position.x > 200 && position.x < 0 && position.y < 0 && position.y > 74)
		isDead = true;

	if (isDead && mType == Type::Missle)
	{
		QueryCallback qc;
		b2AABB aabb;
		b2Vec2 lower(position.x-1.5, position.y-1.5);
		b2Vec2 upper(position.x+1.5, position.y+1.5);
		aabb.lowerBound = lower;
		aabb.upperBound = upper;
		pWorld -> QueryAABB(&qc, aabb); 
	}

 }

 Projectile::~Projectile()
 {
	 if (mType == Type::Missle)
	 {
		std::unique_ptr<Explosion> exp(new Explosion(pWorld, position, mTextures));
		Explosion* newExplosion = exp.get();
		newExplosion->setPosition(b2ToSfmlVec(position).x,b2ToSfmlVec(position).y);
		expHolder->attachChild(std::move(exp));
	 }
	 pWorld -> DestroyBody(projBody);
 }