#include "headers.hpp"

CommandManager::CommandManager(void)
{
	mKeyBinding.insert(keyActionMap::value_type(sf::Keyboard::A, MoveLeft));
	mKeyBinding.insert(keyActionMap::value_type(sf::Keyboard::A, Stop));
	mKeyBinding.insert(keyActionMap::value_type(sf::Keyboard::D, MoveRight));
	mKeyBinding.insert(keyActionMap::value_type(sf::Keyboard::D, Stop));

	mActionBinding[MoveLeft].action = derivedAction<Player>(PlayerMover(-10.f,0.f));
	mActionBinding[MoveRight].action = derivedAction<Player>(PlayerMover(10.f,0.f));

	for(auto& pair: mActionBinding)     
		pair.second.category = Category::Player;
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
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		Command fireAllow;
		fireAllow.category = Category::Player;
		fireAllow.action = derivedAction<Player>( [] (Player& player, sf::Time dt)
		{
			player.isFiring = true;
		});
		commands.push(fireAllow);
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
	mKeyBinding.insert(keyActionMap::value_type(sf::Keyboard::Unknown, EndRealtimeactions));
	mActionBinding[EndRealtimeactions].action = derivedAction<Player>(PlayerMover(0.f,0.f));
	mActionBinding[EndRealtimeactions].category = Category::None;

	mKeyBinding.insert(keyActionMap::value_type(sf::Keyboard::Space, Jump));
	mActionBinding[Jump].action = derivedAction<Player>(PlayerJump(0.f, 10.f));	
	mActionBinding[Jump].category = Category::Player;

	mKeyBinding.insert(keyActionMap::value_type(sf::Keyboard::Q, ChangeWeapon));
	mActionBinding[ChangeWeapon].action = derivedAction<Player>(PlayerChangeWeapon());	
	mActionBinding[ChangeWeapon].category = Category::Player;

 }

