#pragma once
	
#define  playerSpeed   3.f

class CommandManager
{
public:
	enum Action     
	{
		MoveLeft,
		MoveRight,
		EndRealtimeactions,
		Stop,
		Jump,
		ChangeWeapon
	};

	typedef	std::multimap<sf::Keyboard::Key, CommandManager::Action> keyActionMap;

							CommandManager(void);
	void                    handleEvent(const sf::Event& event, CommandQueue& commands); 
	void                    handleRealtimeInput(CommandQueue& commands); 
	void                    assignKey();
	sf::Keyboard::Key       getAssignedKey(Action action) const;

private:
	keyActionMap					    mKeyBinding;
	std::map<Action, Command>			mActionBinding;

	static bool							  isRealtimeAction(Action action);
};


