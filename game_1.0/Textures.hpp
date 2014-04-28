#pragma once
//#include "ResourceHolder.hpp"
//#include "SFML/Graphics.hpp"

namespace Textures
{
	enum ID
	{
		Player,
		Ground,
		TNT,       //--------------------
		Bullet,    // Текстуры снарядов
		Missle,
		Sky,
		Enemy1,
		Enemy2,
		Explosion
	};
}

typedef ResourceHolder<sf::Texture,Textures::ID> TextureHolder;