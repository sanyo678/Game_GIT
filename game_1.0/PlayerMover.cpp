#include "headers.hpp"

PlayerMover::PlayerMover(float vx, float vy)  
		: velocity(vx, vy)
{
}

void PlayerMover::operator()(Player& player, sf::Time dt) const 
{
	b2Vec2 vel = player.body->GetLinearVelocity();
	float velChange = velocity.x - vel.x;
	float impulse = player.body->GetMass() * velChange;
	player.body->ApplyLinearImpulse( b2Vec2(impulse,0), player.body->GetWorldCenter(), true );
}

PlayerJump::PlayerJump(float vx, float vy)  
		: velocity(vx, vy)
{
}

void PlayerJump::operator()(Player& player, sf::Time dt) const 
{
	if (player.onFloor)
	{
		float impulse = player.body->GetMass() * velocity.y;
		player.body->ApplyLinearImpulse( b2Vec2(0,impulse), player.body->GetWorldCenter(), true );
	}
}

PlayerChangeWeapon::PlayerChangeWeapon()  
{
}

void PlayerChangeWeapon::operator()(Player& player, sf::Time dt) const
{
	if (player.currentProj == Projectile::Type::Missle)
	{
		player.currentProj = Projectile::Type::Bullet;
	}
	else
	{
		player.currentProj = Projectile::Type::Missle;
	}
}
