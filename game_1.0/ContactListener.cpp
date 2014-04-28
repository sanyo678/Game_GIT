#include "headers.hpp"


void ContactListener::BeginContact(b2Contact* contact)
{
	SceneNode* A = static_cast<SceneNode*> (contact -> GetFixtureA() -> GetBody() -> GetUserData() );
	SceneNode* B = static_cast<SceneNode*> (contact -> GetFixtureB() -> GetBody() -> GetUserData() );

	if (A -> getCategory() == Category::Projectile && contact->IsTouching())
		A->isDead = true;

						 
	if (B -> getCategory() == Category::Projectile && contact->IsTouching())
		B->isDead = true;
	
	if (contact->IsTouching() &&  //projectile - ground
		(A -> getCategory() == Category::Projectile || B -> getCategory() == Category::Projectile) &&
		(A -> getCategory() == Category::Ground || B -> getCategory() == Category::Ground))
	{
		Ground* ground = static_cast<Ground*>( (A -> getCategory() == Category::Ground) ? A : B);
		Projectile* proj = static_cast<Projectile*>( (A -> getCategory() == Category::Ground) ? B : A );
		if (proj->getType() == Projectile::Type::Missle)
			ground->explosion(proj->position, 3);
	}

	if (contact->IsTouching() &&  //player - ground
		(A -> getCategory() == Category::Player || B -> getCategory() == Category::Player) &&
		(A -> getCategory() == Category::Ground || B -> getCategory() == Category::Ground))
	{
		Player* player = static_cast<Player*>( (A -> getCategory() == Category::Ground) ? B : A );
		player -> onFloor++;
	}

	if (contact->IsTouching() &&  //player - wreck
		(A -> getCategory() == Category::Player || B -> getCategory() == Category::Player) &&
		(A -> getCategory() == Category::Wreck || B -> getCategory() == Category::Wreck))
	{
		Player* player = static_cast<Player*>( (A -> getCategory() == Category::Wreck) ? B : A );
		player -> onFloor++;
	}

	if (contact->IsTouching() &&  //projectile - enemy
		(A -> getCategory() == Category::Projectile || B -> getCategory() == Category::Projectile) &&
		(A -> getCategory() == Category::Enemy || B -> getCategory() == Category::Enemy))
	{
		Enemy* enemy = static_cast<Enemy*>( (A -> getCategory() == Category::Enemy) ? A : B);
		Projectile* proj = static_cast<Projectile*>( (A -> getCategory() == Category::Enemy) ? B : A );
		enemy->hp -= proj->Table[proj->getType()].Damage;
		if (enemy->hp <= 0)
		{
			enemy -> isDead = true;
		}
	}

	if (contact->IsTouching() &&  //player - enemy
		(A -> getCategory() == Category::Player || B -> getCategory() == Category::Player) &&
		(A -> getCategory() == Category::Enemy || B -> getCategory() == Category::Enemy))
	{
		Player* player = static_cast<Player*>( (A -> getCategory() == Category::Enemy) ? B : A );
		player->isHurting = true;
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	SceneNode* A = static_cast<SceneNode*> (contact -> GetFixtureA() -> GetBody() -> GetUserData() );
	SceneNode* B = static_cast<SceneNode*> (contact -> GetFixtureB() -> GetBody() -> GetUserData() );
	if (  //player - ground
		(A -> getCategory() == Category::Player || B -> getCategory() == Category::Player) &&
		(A -> getCategory() == Category::Ground || B -> getCategory() == Category::Ground))
	{
		Player* player = static_cast<Player*>( (A -> getCategory() == Category::Ground) ? B : A );
		player -> onFloor--;
	}

	if (  //player - wreck
		(A -> getCategory() == Category::Player || B -> getCategory() == Category::Player) &&
		(A -> getCategory() == Category::Wreck || B -> getCategory() == Category::Wreck))
	{
		Player* player = static_cast<Player*>( (A -> getCategory() == Category::Wreck) ? B : A );
		player -> onFloor--;
	}

	if (  //player - enemy
		(A -> getCategory() == Category::Player || B -> getCategory() == Category::Player) &&
		(A -> getCategory() == Category::Enemy || B -> getCategory() == Category::Enemy))
	{
		Player* player = static_cast<Player*>( (A -> getCategory() == Category::Enemy) ? B : A );
		player->isHurting = false;
	}
}
