#include "headers.hpp"

std::vector<ProjectileData> initializeProjectileData()
{
	std::vector<ProjectileData> data(Projectile::TypeCount);

	data[Projectile::Bullet].StartVelocity.x = 150.f;
	data[Projectile::Bullet].StartVelocity.y = 0.f;
	data[Projectile::Bullet].Damage = 20.f;
	data[Projectile::Bullet].texture = Textures::ID::Bullet;

	data[Projectile::Rocket].StartVelocity.x = 350.f;
	data[Projectile::Rocket].StartVelocity.x = 0.f;
	data[Projectile::Rocket].Damage = 35.f;  
	data[Projectile::Rocket].texture = Textures::ID::Rocket;

	data[Projectile::TNT].StartVelocity.x = 40.f;
	data[Projectile::TNT].StartVelocity.y = 0.f;
	data[Projectile::TNT].Damage = 25.f;
	data[Projectile::TNT].texture = Textures::ID::TNT;

	return data; 
}