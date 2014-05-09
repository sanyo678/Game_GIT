#include "headers.hpp"

ContactListener listener; //global scope

World::World(sf::RenderWindow& window):
	mWindow(window),
	mWorldBounds(
		0.f,
		0.f,
		4097.0f,
		705.0f),
	mSpawnPosition(
		120,
		55),
	mPlayer(nullptr),
	mCamera(new Camera( sf::View() )),
	mSceneGraph(physWorld),
	enemyCountDown(10.0)
{
	physWorld = new b2World(b2Vec2(0,-9.8));
	mCamera->view.reset(sf::FloatRect(mSpawnPosition.x,mSpawnPosition.y, 1920, 1440));
	mCamera->view.setCenter(b2ToSfmlVec(mSpawnPosition).x,b2ToSfmlVec(mSpawnPosition).y);
	mCamera->viewCenter = sf::Vector2f(b2ToSfmlVec(mSpawnPosition).x,b2ToSfmlVec(mSpawnPosition).y);
	mWindow.setView(mCamera->view);
	fonts.load(Fonts::main, "media/Fonts/Washington.ttf");
	physWorld->SetContactListener(&listener);
	loadTextures();
	buildScene();
	srand(time(NULL));
}

void World::loadTextures()
{
	mTextures.load(Textures::Player, "media/Textures/testPlayer.png");
	mTextures.load(Textures::Ground, "media/Textures/ground3.png");
	mTextures.load(Textures::Missle, "media/Textures/missle.png");
	mTextures.load(Textures::Bullet, "media/Textures/bullet.png");
	mTextures.load(Textures::Sky, "media/Textures/sky.png");
	mTextures.load(Textures::Enemy1, "media/Textures/Enemy1.png");
	mTextures.load(Textures::Enemy2, "media/Textures/Enemy2.png");
	mTextures.load(Textures::Explosion, "media/Textures/explosion1.png");
}

void World::buildScene()
{
	for (std::size_t i = 0; i<LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode(physWorld));
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}
	std::unique_ptr<Player> player(new Player(mSpawnPosition, mTextures, physWorld, mWindow, mSceneLayers[Projectiles], mSceneLayers[Frontside]));
	mPlayer = player.get();
	mPlayer->setPosition(b2ToSfmlVec(mSpawnPosition).x,b2ToSfmlVec(mSpawnPosition).y);
	mSceneLayers[Frontside]->attachChild(std::move(player));

	std::unique_ptr<Ground> ground(new Ground(mTextures, physWorld, mSceneLayers[Wrecks]));
	mGround = ground.get();
	mGround->setPosition(0.0f, 1000.0f);
	mSceneLayers[Background]->attachChild(std::move(ground));

	std::unique_ptr<TextNode> timer(new TextNode(physWorld, fonts, std::to_string(0.0)));
	mTimer = timer.get();
	mTimer->setPosition(-920,-700);
	mPlayer->attachChild(std::move(timer));

	mCamera->setTarget(mPlayer);
}

void World::draw()
{
	mWindow.setView(mCamera->view);
	mWindow.draw(mSceneGraph);//с учетом view
}

void World::addEnemy()
{
	srand(time(NULL));
	b2Vec2 spawn(80+rand()%50,50);
	std::unique_ptr<Enemy> enemy(new Enemy(physWorld, spawn, mTextures));
	Enemy* newEnemy = enemy.get();
	newEnemy->setPosition(b2ToSfmlVec(spawn).x,b2ToSfmlVec(spawn).y);
	mSceneLayers[Frontside]->attachChild(std::move(enemy));
}


void World::update(sf::Time dt)
{   
	mPlayer -> checkProjectileLaunch(dt, mCommandQueue);//проверка - можно ли стрелять

	mTimer->lifetime += dt.asSeconds();
	mTimer->setString(std::to_string(mTimer->lifetime));

	while (!mCommandQueue.isEmpty())   
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);		
	
	enemyCountDown-=dt.asSeconds();
	if (enemyCountDown<=0)
	{
		addEnemy();
		enemyCountDown = 3;
	}

	mCamera->update();
	//-------------------
	physWorld->Step(1.0f / 60.0f, 3 , 1);
	//-------------------
	try
	{
		mSceneGraph.update(dt);
	}
	catch (bool)
	{
		throw mTimer->lifetime;
	}
	mSceneGraph.removeDead();
}

CommandQueue& World::getCommandQueue() 
{
	 return mCommandQueue; 
}

World::~World()
{
	delete physWorld;
	delete mCamera;
}

