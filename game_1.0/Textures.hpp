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
		Rocket
	};
}

typedef ResourceHolder<sf::Texture,Textures::ID> TextureHolder;