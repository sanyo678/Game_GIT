#include "Game.hpp"


Game::Game()
	:mWindow(sf::VideoMode(800, 600), "Game_v_1.0", sf::Style::Close),
	mWorld(mWindow),
	TimePerFrame(sf::seconds(1.f/60.f))
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSincLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();
		timeSincLastUpdate += clock.restart();
		while (timeSincLastUpdate > TimePerFrame)
		{
			timeSincLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();
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



