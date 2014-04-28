#include "headers.hpp"

bool QueryCallback::ReportFixture(b2Fixture* fixture)
{
	SceneNode* A = static_cast<SceneNode*> (fixture -> GetBody() -> GetUserData() );
	if (A->getCategory() != Category::Ground)
	{
		A->explosionImpulse = b2Vec2(rand()%2000 - 1000, rand()%1000);
	}

	if (A->getCategory() == Category::Enemy)
	{
		Enemy* enemy = static_cast<Enemy*>(A);
		enemy->hp -= 15;
		if (enemy->hp <= 0)
		{
			enemy->isDead = true;
		}
	}

	return true;
}

