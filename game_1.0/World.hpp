#pragma once
#include "SFML/Graphics.hpp"
#include "Textures.hpp"	
#include "SceneNode.hpp"
#include "Player.hpp"
#include "CommandQueue.hpp"
#include <array>
#define PlayerSpeed 70.f

class World
{
public:
	explicit		World(sf::RenderWindow& window);
	void			update(sf::Time dt);
	void			draw();
	CommandQueue&   getCommandQueue(); 
	Player&         getPlayerRef();

private:
	void			loadTextures();
	void			buildScene();

private:
	enum Layer
	{
		Background,		  //задний план
		Frontside,		  //передний план
		LayerCount
	};

private:
	sf::RenderWindow&					mWindow;
	sf::View							mWorldView;		
	TextureHolder						mTextures;		//см ResourceHolder.hpp + Textures.hpp
	SceneNode							mSceneGraph;	//корень дерева объектов
	std::array<SceneNode*, LayerCount>	mSceneLayers;	//корни слоев
	sf::FloatRect						mWorldBounds;	//границы мира, нужно заменить на эквивалент из Box2D
	sf::Vector2f						mSpawnPosition;	//нужно заменить на эквивалент из Box2D
	Player*								mPlayer;		//персонаж
	CommandQueue                        mCommandQueue;  //очередь комманд
};

