#pragma once

namespace Textures
{
	enum ID
	{
		Player,
		Ground,
		TNT,      
		Bullet,
		Missle,
		Sky,
		Enemy1,
		Enemy2,
		Explosion
	};
}

typedef ResourceHolder<sf::Texture,Textures::ID> TextureHolder;