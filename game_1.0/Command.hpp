#pragma once
//#include <functional> //для std::function<>
//#include "SFML/Graphics.hpp"
//#include "SceneNode.hpp"


namespace Category
{   
	enum Type  
	{     
		None        = 0,   
		Scene       = 1 << 0,
		FrontSide   = 1 << 1,
		BackSide    = 1 << 2,
		Player		= 1 << 3,
		Ground		= 1 << 4,
		Projectile	= 1 << 5,
		Wreck       = 1 << 6,
		Enemy       = 1 << 7
	};
} 

class SceneNode;

struct Command
{   
	Command();
	~Command();

	std::function<void(SceneNode&, sf::Time)>    action; 
	unsigned int                                 category;
	//char*										 name;
};
