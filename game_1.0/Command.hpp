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
		RedPlayer   = 1 << 1,
		BluePlayer  = 1 << 2,
		Projectile	= 1 << 3
	};
} 

struct Command
{   
	Command();

	std::function<void(SceneNode&, sf::Time)>    action; 
	unsigned int                                 category;
};
