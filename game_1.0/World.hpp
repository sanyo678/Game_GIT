#pragma once
#include "SFML/Graphics.hpp"
#include "Textures.hpp"	
#include "SceneNode.hpp"
#include "Player.hpp"
#include "CommandQueue.hpp"
#include <array>
#include "Ground.hpp"
#include "Camera.hpp"

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
		Background,		  //������ ����
		Frontside,		  //�������� ����
		LayerCount
	};

private:
	sf::RenderWindow&					mWindow;
	Camera*								mCamera;
	TextureHolder						mTextures;		//�� ResourceHolder.hpp + Textures.hpp
	SceneNode							mSceneGraph;	//������ ������ ��������
	std::array<SceneNode*, LayerCount>	mSceneLayers;	//����� �����
	sf::FloatRect						mWorldBounds;	//������� ����, ����� �������� �� ���������� �� Box2D
	sf::Vector2f						mSpawnPosition;	//����� �������� �� ���������� �� Box2D
	Player*								mPlayer;		//��������
	Ground*								mGround;
	CommandQueue                        mCommandQueue;  //������� �������
};

