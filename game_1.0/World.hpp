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
		Background,		  //������ ����
		Frontside,		  //�������� ����
		Projectiles,      //missles etc.
		Wrecks,
		LayerCount
	};

	sf::RenderWindow&					mWindow;
	Camera*								mCamera;
	TextureHolder						mTextures;		//�� ResourceHolder.hpp + Textures.hpp
	SceneNode							mSceneGraph;	//������ ������ ��������
	std::array<SceneNode*, LayerCount>	mSceneLayers;	//����� �����
	sf::FloatRect						mWorldBounds;	
	b2Vec2								mSpawnPosition;	
	Player*								mPlayer;		//��������
	Ground*								mGround;
	CommandQueue                        mCommandQueue;  //������� �������
	float								enemyCountDown;
	TextNode*							mTimer;
	FontHolder							fonts;
};

