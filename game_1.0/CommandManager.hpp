#pragma once
#include <map>
#include "SFML/Graphics.hpp"
#include "CommandQueue.hpp"
#define  playerSpeed   3.f

class CommandManager
{
public:
	enum Action     
	{
		MoveLeft,
		MoveRight,
		EndRealtimeactions,
		Jump
	};

							CommandManager(void);
	void                    handleEvent(const sf::Event& event, CommandQueue& commands); 
	void                    handleRealtimeInput(CommandQueue& commands); 
	void                    assignKey();
	sf::Keyboard::Key       getAssignedKey(Action action) const;
private:
	std::map<sf::Keyboard::Key, Action>   mKeyBinding;
	std::map<Action, Command>             mActionBinding;

	static bool							  isRealtimeAction(Action action);
};

