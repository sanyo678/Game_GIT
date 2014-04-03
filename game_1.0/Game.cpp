#include "headers.hpp"


Game::Game()
	:mWindow(sf::VideoMode(800, 600), "Game_v_1.0", sf::Style::Close),	
	mWorld(mWindow),
	TimePerFrame(sf::seconds(1.f/60.f)),
	mIsPaused(false)
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSincLastUpdate = sf::Time::Zero;
	mManager.assignKey();
	while (mWindow.isOpen())
	{

		processInput();
		timeSincLastUpdate += clock.restart();
		while (timeSincLastUpdate > TimePerFrame)
		{
			timeSincLastUpdate -= TimePerFrame;
			if (!mIsPaused)    
				update(TimePerFrame);
		}
		render(); 
		 				
	}
}


void Game::update(sf::Time dt)
{
	mWorld.update(dt);
}

void Game::render()
{
	mWindow.clear();
	mWorld.draw();
	mWindow.display();
}

void Game::processInput() 
{   
	//Player& mPlayer = mWorld.getPlayerRef();
	CommandQueue& commands = mWorld.getCommandQueue();
	sf::Event event; 
	while (mWindow.pollEvent(event)) 
	{      
		mManager.handleEvent(event, commands);

		if (event.type == sf::Event::GainedFocus)   
			mIsPaused = false;   
		else if (event.type == sf::Event::LostFocus)
			mIsPaused = true;
		else if (event.type == sf::Event::Closed)   
			mWindow.close();  
	}
	mManager.handleRealtimeInput(commands); 
}


