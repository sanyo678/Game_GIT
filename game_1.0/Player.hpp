#pragma once
#include "Entity.hpp"
#include "SceneNode.hpp"
#include "Textures.hpp"
#include "Command.hpp"


class Player : public Entity
{
public:	
	enum Type       
	{            
		Red,        // тип игрока RedPlayer
		Blue,       // BluePlayer
	};

public:
					        Player(const TextureHolder& textures);
	virtual void	        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual unsigned int    getCategory() const;

private:
	sf::Sprite							  mSprite;
	Type								  mType;
};

