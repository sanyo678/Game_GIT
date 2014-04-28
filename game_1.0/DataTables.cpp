#include "headers.hpp"

std::vector<ProjectileData> initializeProjectileData()
{
	std::vector<ProjectileData> data(Projectile::TypeCount);

	data[Projectile::Bullet].StartVelocity = 3;
	data[Projectile::Bullet].Damage = 5;
	data[Projectile::Bullet].texture = Textures::ID::Bullet;
	data[Projectile::Bullet].countdown = 0.2f;
	data[Projectile::Bullet].buildBody = [] (Projectile& proj, b2Vec2 pos, b2Vec2 dir)
	{
		b2BodyDef BulletBodyDef;
		BulletBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		b2Vec2 offset = b2Vec2(2*dir.x / (length(dir)),3*dir.y / (length(dir)) ); //2*length
		BulletBodyDef.position.Set((pos+offset).x,(pos+offset).y); //set the starting position
		BulletBodyDef.bullet = true;

		proj.projBody = proj.pWorld->CreateBody(&BulletBodyDef);

		b2CircleShape circleShape;
		circleShape.m_p.Set(0, 0); //position, relative to body position
		circleShape.m_radius = 0.05; //radius

		b2FixtureDef bulletCircleFixtureDef;
		bulletCircleFixtureDef.shape = &circleShape;
		bulletCircleFixtureDef.density = 5000;
		proj.projBody->CreateFixture(&bulletCircleFixtureDef);
		proj.projBody -> SetGravityScale(0);
	};

	data[Projectile::Missle].StartVelocity = 3;
	data[Projectile::Missle].Damage = 20;  
	data[Projectile::Missle].texture = Textures::ID::Missle;
	data[Projectile::Missle].countdown = 1.0f;
	data[Projectile::Missle].buildBody = [] (Projectile& proj, b2Vec2 Pos, b2Vec2 dir)
	{
		b2BodyDef MissleBodyDef;
		MissleBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		b2Vec2 offset = b2Vec2(5* dir.x / (length(dir)),5* dir.y / (length(dir)) ); //2*length
		MissleBodyDef.position.Set((Pos+offset).x,(Pos+offset).y); //set the starting position
		MissleBodyDef.bullet = true;

		proj.projBody = proj.pWorld->CreateBody(&MissleBodyDef);

		b2CircleShape circleShape;
		circleShape.m_p.Set(0, 0); //position, relative to body position
		circleShape.m_radius = 0.05; //radius

		b2FixtureDef missleCircleFixtureDef;
		missleCircleFixtureDef.shape = &circleShape;
		missleCircleFixtureDef.density = 5000;
		missleCircleFixtureDef.friction=10;
		proj.projBody->CreateFixture(&missleCircleFixtureDef);
  
		b2PolygonShape rectShape;
		b2FixtureDef missleRectFixtureDef;
		missleRectFixtureDef.shape = &rectShape;
		missleRectFixtureDef.density = 100;
		b2Vec2 pos(0.0f , -0.2f);
		rectShape.SetAsBox(0.05f, 0.15, pos , 0 );
		proj.projBody->CreateFixture(&missleRectFixtureDef);
	};

	data[Projectile::TNT].StartVelocity = 40.f;
	data[Projectile::TNT].Damage = 25.f;
	data[Projectile::TNT].texture = Textures::ID::TNT;
	data[Projectile::TNT].buildBody = [] (Projectile& proj, b2Vec2 pos, b2Vec2 dir)
	{
	};

	return data; 
}