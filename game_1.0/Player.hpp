#pragma once
#include "Entity.hpp"
#include "SceneNode.hpp"
#include "SFML/Graphics.hpp"
#include "Textures.hpp"

class Player : public Entity
{
public:
					Player(const TextureHolder& textures);
	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite		mSprite;
};

