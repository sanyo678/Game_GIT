#pragma once
#include "Game.hpp"


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
	//Player& mplayer = mWorld.getPlayerRef();
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
	//
		  std::vector<sf::Vertex> vertices;
		  vertices.push_back(sf::Vertex(sf::Vector2f(10, 50), sf::Color::Red));
		  vertices.push_back(sf::Vertex(sf::Vector2f(70, 50), sf::Color::Green));
		  vertices.push_back(sf::Vertex(sf::Vector2f(70, 100), sf::Color::Blue));
		  mWindow.draw(&vertices[0], vertices.size(), sf::Triangles);
		//
	mWorld.draw();
	mWindow.display();
}

void Game::processInput() 
{   
	Player& mPlayer = mWorld.getPlayerRef();
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


