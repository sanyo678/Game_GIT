#include "CommandManager.hpp"
#include "ActionAdapter.hpp"
#include "PlayerMover.hpp"


CommandManager::CommandManager(void)
{
	mKeyBinding[sf::Keyboard::A] = MoveLeft; 
	mKeyBinding[sf::Keyboard::D] = MoveRight;

	mActionBinding[MoveLeft].action =    [] (SceneNode& node, sf::Time dt)
	{
		node.move(-playerSpeed * dt.asSeconds(), 0.f);   
	};
	mActionBinding[MoveRight].action =  [] (SceneNode& node, sf::Time dt) 
	{
		node.move(playerSpeed * dt.asSeconds(), 0.f);  
	};

	for(auto& pair: mActionBinding)     
		pair.second.category = Category::RedPlayer;
}

void CommandManager::handleRealtimeInput(CommandQueue& commands) 
{
	
	for(auto pair : mKeyBinding) 
	{
		if (sf::Keyboard::isKeyPressed(pair.first) 
			&& isRealtimeAction(pair.second))   
			commands.push(mActionBinding[pair.second]); 
	}         
}

void CommandManager::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	for(auto pair : mKeyBinding) 
	{
		if (event.type == sf::Event::KeyReleased && event.key.code == (pair.first) 
			&& (!(isRealtimeAction(pair.second))) )  
			commands.push(mActionBinding[pair.second]); 
	}  	
}

bool CommandManager::isRealtimeAction(Action act)
{
	if (act >= EndRealtimeactions)
		return false;
	else return true;
}

sf::Keyboard::Key  CommandManager::getAssignedKey(Action action) const
 {
	 for(auto pair : mKeyBinding) 
	 {
		 if(action == pair.second)
			 return pair.first;
	 }
	 return sf::Keyboard::Unknown;
 }

void CommandManager::assignKey()
 {
	mKeyBinding[sf::Keyboard::Unknown] = EndRealtimeactions;
	mActionBinding[EndRealtimeactions].action = derivedAction<Player>(PlayerMover(0.f,0.f));
	mActionBinding[EndRealtimeactions].category = Category::None;

	mKeyBinding[sf::Keyboard::Space] = Jump;
	mActionBinding[Jump].action = derivedAction<Player>(PlayerMover(0.f,-100.f));	
	mActionBinding[Jump].category = Category::RedPlayer;


 }

