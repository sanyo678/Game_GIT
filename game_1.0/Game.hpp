#pragma once
//#include "SFML/Graphics.hpp"
//#include "World.hpp"
//#include "CommandManager.hpp"

class Game
{
public:
					Game();
	void			run();

	CommandManager	mManager; 

private:
	//void	processEvents();
	void	update(sf::Time dt);
	void	render();
	void    processInput(); 

private:
	sf::RenderWindow	mWindow;
	World				mWorld;
	sf::Time			TimePerFrame;
	bool                mIsPaused;
};

