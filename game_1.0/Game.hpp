#pragma once
#include "SFML/Graphics.hpp"
#include "World.hpp"
class Game
{
public:
			Game();
	void	run();

private:
	void	processEvents();
	void	update(sf::Time dt);
	void	render();
	void    processInput(); 

private:
	sf::RenderWindow	mWindow;
	World				mWorld;
	sf::Time			TimePerFrame;
	bool                mIsPaused;
};

