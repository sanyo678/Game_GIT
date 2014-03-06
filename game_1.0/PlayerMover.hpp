#pragma once
#include "Player.hpp"
#include "ActionAdapter.hpp"

struct PlayerMover
{
	PlayerMover(float vx, float vy)  
		: velocity(vx, vy)
	{};

	void	operator()(Player& player, sf::Time dt) const 
	{
		player.setVelocity(player.getVelocity() + velocity);
	};

	sf::Vector2f	velocity; 
}; 