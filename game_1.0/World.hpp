#pragma once
//#include "SFML/Graphics.hpp"
//#include "Textures.hpp"	
//#include "SceneNode.hpp"
//#include "Player.hpp"
//#include "CommandQueue.hpp"
//#include <array>
//#include "Ground.hpp"
//#include "Camera.hpp"
//#include "Box2D/Box2D.h"
//#include "convertions.hpp"

#define PlayerSpeed 70.f

class World
{
public:
	explicit		World(sf::RenderWindow& window);
					~World();
	void			update(sf::Time dt);
	void			draw();
	CommandQueue&   getCommandQueue(); 

	b2World*		physWorld; 

private:
	void			loadTextures();
	void			buildScene();
	void			addEnemy();

private:
	enum Layer
	{
		Background,		  //задний план
		Frontside,		  //передний план
		Projectiles,      //missles etc.
		Wrecks,
		LayerCount
	};

private:
	sf::RenderWindow&					mWindow;
	Camera*								mCamera;
	TextureHolder						mTextures;		//см ResourceHolder.hpp + Textures.hpp
	SceneNode							mSceneGraph;	//корень дерева объектов
	std::array<SceneNode*, LayerCount>	mSceneLayers;	//корни слоев
	sf::FloatRect						mWorldBounds;	//границы мира, нужно заменить на эквивалент из Box2D
	b2Vec2								mSpawnPosition;	//нужно заменить на эквивалент из Box2D
	Player*								mPlayer;		//персонаж
	Ground*								mGround;
	CommandQueue                        mCommandQueue;  //очередь комманд
	float								enemyCountDown;
};

