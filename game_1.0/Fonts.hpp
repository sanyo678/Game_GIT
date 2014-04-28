#pragma once

namespace Fonts
{
	enum ID
	{
		main
	};
}

typedef ResourceHolder<sf::Font,Fonts::ID> FontHolder;