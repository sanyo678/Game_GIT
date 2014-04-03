#include "headers.hpp"


World::World(sf::RenderWindow& window):
	mWindow(window),
	mWorldBounds(
		0.f,
		0.f,
		4097.0f,
		705.0f),
	mSpawnPosition(
		10,
		38),
	mPlayer(nullptr),
	mCamera(new Camera( sf::View() )),
	mSceneGraph(physWorld)
{
	physWorld = new b2World(b2Vec2(0,-9.8));
	//mCamera->view.reset(sf::FloatRect(-10, -10, 8000, 6000));
	//mCamera->view = mWindow.getDefaultView();
	mCamera->view.reset(sf::FloatRect(mSpawnPosition.x,mSpawnPosition.y, 800, 600));
	mCamera->view.setCenter(b2ToSfmlVec(mSpawnPosition).x,b2ToSfmlVec(mSpawnPosition).y);
	mCamera->viewCenter = sf::Vector2f(b2ToSfmlVec(mSpawnPosition).x,b2ToSfmlVec(mSpawnPosition).y);
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
		SceneNode::Ptr layer(new SceneNode(physWorld));
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}
	std::unique_ptr<Player> player(new Player(mSpawnPosition, mTextures, physWorld, mWindow));
	mPlayer = player.get();
	//mPlayer->position = mSpawnPosition;					    //нужно заменить на эквивалент из Box2D
	mPlayer->setPosition(b2ToSfmlVec(mSpawnPosition).x,b2ToSfmlVec(mSpawnPosition).y);
	//mPlayer->mSprite.setPosition(b2ToSfmlVec(mSpawnPosition).x,b2ToSfmlVec(mSpawnPosition).y);
	mSceneLayers[Frontside]->attachChild(std::move(player));

	std::unique_ptr<Ground> ground(new Ground(mTextures, physWorld));
	mGround = ground.get();
	mGround->setPosition(0.0f, 300.0f);
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
	mPlayer -> checkProjectileLaunch(dt, mCommandQueue);//проверка - можно ли стрелять

	while (!mCommandQueue.isEmpty())   
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);		
	
	mCamera->update();
	//-------------------
	physWorld->Step(1.0f / 60.0f, 6 ,2);
	//-------------------
	mSceneGraph.update(dt);
}

CommandQueue& World::getCommandQueue() 
{
	 return mCommandQueue; 
}

World::~World()
{
	delete mCamera;
	delete physWorld;
}

