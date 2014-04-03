#pragma  once

struct ProjectileData
{
	sf::Vector2f   StartVelocity;
	float          Damage;
	Textures::ID   texture;
};

std::vector<ProjectileData>  initializeProjectileData();