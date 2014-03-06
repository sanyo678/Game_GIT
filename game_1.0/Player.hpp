#pragma once
#include "Entity.hpp"
#include "SceneNode.hpp"
#include "SFML/Graphics.hpp"
#include "Textures.hpp"
#include "CommandQueue.hpp"


class Player : public Entity
{
public:	
	enum Action     
	{
		MoveLeft,
		MoveRight,
		EndRealtimeactions,
		Jump
	};

	enum Type       
	{            
		Red,        // тип игрока RedPlayer
		Blue,       // BluePlayer
	};

public:
					        Player(const TextureHolder& textures);
	virtual void	        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual unsigned int    getCategory() const;
    void                    handleEvent(const sf::Event& event, CommandQueue& commands); 
	void                    handleRealtimeInput(CommandQueue& commands); 
	void                    assignKey();
	sf::Keyboard::Key       getAssignedKey(Action action) const;

private:
	static bool             isRealtimeAction(Action action);

private:
	sf::Sprite							  mSprite;
	Type								  mType;
	std::map<sf::Keyboard::Key, Action>   mKeyBinding;
	std::map<Action, Command>             mActionBinding; 
};

