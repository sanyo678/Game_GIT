#pragma once

struct PlayerMover
{
					PlayerMover(float vx, float vy); 
	void			operator()(Player& player, sf::Time dt) const ;
	b2Vec2			velocity; 
}; 

struct PlayerJump
{
					PlayerJump(float vx, float vy);
	void			operator()(Player& player, sf::Time dt) const;
	b2Vec2			velocity; 
};

struct PlayerChangeWeapon
{
					PlayerChangeWeapon();
	void			operator()(Player& player, sf::Time dt) const; 
};