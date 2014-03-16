#pragma once
#include "ResourceHolder.hpp"
#include "SFML/Graphics.hpp"

namespace Textures
{
	enum ID
	{
		Player,
		Ground,
	};
}

typedef ResourceHolder<sf::Texture,Textures::ID> TextureHolder;