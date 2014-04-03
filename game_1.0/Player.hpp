#pragma once
//#include "SceneNode.hpp"
//#include "Textures.hpp"
//#include "Command.hpp"
//#include "convertions.hpp"




class Player : public SceneNode
{
public:	
	enum Type       
	{            
		Red,        // тип игрока RedPlayer
		Blue,       // BluePlayer
	};

public:
	b2Body*					body;
	bool					onFloor;
	bool					isFiring; //стрелять или нет. привязать down count
	Command					fireCommand;//комада стрелять
	sf::Sprite				mSprite;
	b2Vec2					firingDirection;//направление стрельбы
	sf::Vector2f			windowOffset; //смещение игрока относительно окна(пока const, =0)
	sf::RenderWindow&		window;

							Player(const b2Vec2, const TextureHolder& textures, b2World* _pWorld, sf::RenderWindow&);
	virtual void	        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			updateCurrent(sf::Time);
	virtual unsigned int    getCategory() const;
	void					checkProjectileLaunch(sf::Time, CommandQueue&);
	void					updateFiringDirection();

private:
	b2Vec2					getB2Position();
	Type					mType;
	
};

