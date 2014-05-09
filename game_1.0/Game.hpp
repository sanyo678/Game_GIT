#pragma once

class Game
{
public:
								Game();
	void						run();
	CommandManager				mManager; 

private:
	void						update(sf::Time dt);
	void						render();
	void						processInput(sf::Time dt); 

	sf::RenderWindow			mWindow;
	World						mWorld;
	sf::Time					TimePerFrame;
	float						countdown;
	bool						mIsPaused;
};						

