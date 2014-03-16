#pragma once
#include "World.hpp"


World::World(sf::RenderWindow& window):
	mWindow(window),
	mWorldBounds(
		0.f,
		0.f,
		4097.0f,
		705.0f),
	mSpawnPosition(
		100,
		100),
	mPlayer(nullptr),
	mCamera(new Camera( sf::View() ))
{
	mCamera->view.reset(sf::FloatRect(mSpawnPosition.x,mSpawnPosition.y, 800, 600));
	mCamera->view.setCenter( mSpawnPosition.x,mSpawnPosition.y);
	mWindow.setView(mCamera->view);
	loadTextures();
	buildScene();
}

void World::loadTextures()
{
	mTextures.load(Textures::Player, "media/Textures/testPlayer.png");
	mTextures.load(Textures::Ground, "media/Textures/ground1.png");
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

	std::unique_ptr<Ground> ground(new Ground(mTextures));
	mGround = ground.get();
	mSceneLayers[Background]->attachChild(std::move(ground));

	mCamera->setTarget(mPlayer);
}

void World::draw()
{
	mWindow.setView(mCamera->view);
	mWindow.draw(mSceneGraph);	//Draw a drawable(!) object to the render-target(смотри sfml-dev.org)	с учетом view
}

void World::update(sf::Time dt)
{    
	while (!mCommandQueue.isEmpty())   
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);		
	
	mCamera->update();
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