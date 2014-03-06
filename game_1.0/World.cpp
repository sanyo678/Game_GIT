#pragma once
#include "World.hpp"


World::World(sf::RenderWindow& window):
	mWindow(window),
	mWorldView(window.getDefaultView()),
	mWorldBounds(
	0.f,
	0.f,
	mWorldView.getSize().x,
	mWorldView.getSize().y),
	mSpawnPosition(
	mWorldView.getSize().x / 2.f,
	mWorldView.getSize().y / 2.f),
	mPlayer(nullptr)
{
	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures()
{
	mTextures.load(Textures::Player, "media/Textures/testPlayer.png");
}

void World::buildScene()
{
	for (std::size_t i = 0; i<LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}
	std::unique_ptr<Player> player(new Player(mTextures));
	mPlayer = player.get();
	mPlayer->setPosition(mSpawnPosition);					    //нужно заменить на эквивалент из Box2D
	mSceneLayers[Frontside]->attachChild(std::move(player));
}

void World::draw()
{
	//mWindow.setView(mWorldView);	//пока не нужно
	mWindow.draw(mSceneGraph);	//Draw a drawable(!) object to the render-target(смотри sfml-dev.org)
}

void World::update(sf::Time dt)
{    
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f,
		mWorldView.getSize());
	const float borderDistance = 70.f; //подкорректировать под текстуру игрока

	while (!mCommandQueue.isEmpty())   
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);		
	
	 //sf::Vector2f position = mPlayer->getPosition();									       //
	 //position.x = std::max(position.x, viewBounds.left + borderDistance);                      // ограничение игрока 
	 //position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);   // что бы не выходил за границы	
	 //position.y = std::max(position.y, viewBounds.top + borderDistance);                       //
	 //position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);   //
	 //mPlayer->setPosition(position); 
	//-------------------
	//здесь step() из Box2D. Вроде бы
	//-------------------
	mSceneGraph.update(dt);
}

CommandQueue& World::getCommandQueue() 
{
	 return mCommandQueue; 
}

Player&  World::getPlayerRef()
{
	return *mPlayer;
}