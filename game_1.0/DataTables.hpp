#pragma  once

class Projectile;

struct ProjectileData
{
	int														StartVelocity;
	float													Damage;
	Textures::ID											texture;
	bool													gravityDep;
	float													countdown;
	std::function<void(Projectile&, b2Vec2, b2Vec2)>		buildBody;
};

std::vector<ProjectileData>  initializeProjectileData();