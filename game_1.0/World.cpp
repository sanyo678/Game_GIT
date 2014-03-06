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
	mPlayer->setPosition(mSpawnPosition);					    //����� �������� �� ���������� �� Box2D
	mSceneLayers[Frontside]->attachChild(std::move(player));
}

void World::draw()
{
	//mWindow.setView(mWorldView);	//���� �� �����
	mWindow.draw(mSceneGraph);	//Draw a drawable(!) object to the render-target(������ sfml-dev.org)
}

void World::update(sf::Time dt)
{    
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f,
		mWorldView.getSize());
	const float borderDistance = 70.f; //����������������� ��� �������� ������

	while (!mCommandQueue.isEmpty())   
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);		
	
	 //sf::Vector2f position = mPlayer->getPosition();									       //
	 //position.x = std::max(position.x, viewBounds.left + borderDistance);                      // ����������� ������ 
	 //position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);   // ��� �� �� ������� �� �������	
	 //position.y = std::max(position.y, viewBounds.top + borderDistance);                       //
	 //position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);   //
	 //mPlayer->setPosition(position); 
	//-------------------
	//����� step() �� Box2D. ����� ��
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