#pragma once
#include "SFML/Graphics.hpp"
#include "Textures.hpp"
#include "SceneNode.hpp"

class Ground : public SceneNode
{
public:
	sf::Sprite				mSprite;
	sf::IntRect				textureRect;

	virtual void	        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
							Ground(const TextureHolder&);
							~Ground(void);
};

