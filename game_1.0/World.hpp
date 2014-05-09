#pragma once

class World
{
public:
	explicit							World(sf::RenderWindow& window);
										~World();
	void								update(sf::Time dt);
	void								draw();
	CommandQueue&						getCommandQueue(); 

	b2World*							physWorld; 

private:
	void								loadTextures();
	void								buildScene();
	void								addEnemy();

	enum Layer
	{
		Background,		  //задний план
		Frontside,		  //передний план
		Projectiles,      //missles etc.
		Wrecks,
		LayerCount
	};

	sf::RenderWindow&					mWindow;
	Camera*								mCamera;
	TextureHolder						mTextures;		//см ResourceHolder.hpp + Textures.hpp
	SceneNode							mSceneGraph;	//корень дерева объектов
	std::array<SceneNode*, LayerCount>	mSceneLayers;	//корни слоев
	sf::FloatRect						mWorldBounds;	
	b2Vec2								mSpawnPosition;	
	Player*								mPlayer;		//персонаж
	Ground*								mGround;
	CommandQueue                        mCommandQueue;  //очередь комманд
	float								enemyCountDown;
	TextNode*							mTimer;
	FontHolder							fonts;
};

