#pragma once
#include "Player.hpp"
#include "PlayerMover.hpp"
#include <iostream>
#define  playerSpeed   3.f


Player::Player(const TextureHolder& textures) : mSprite(textures.get(Textures::Player)), mType(Red)
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

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

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned int Player::getCategory() const 
{
	switch (mType) 
	{       
	case Red:  
		return Category::RedPlayer;
	default: 
		return Category::BluePlayer; 
	} 
}

void Player::handleRealtimeInput(CommandQueue& commands) 
{
	
	for(auto pair : mKeyBinding) 
	{
		if (sf::Keyboard::isKeyPressed(pair.first) 
			&& isRealtimeAction(pair.second))   
			commands.push(mActionBinding[pair.second]); 
	}         
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	for(auto pair : mKeyBinding) 
	{
		if (event.type == sf::Event::KeyReleased && event.key.code == (pair.first) 
			&& (!(isRealtimeAction(pair.second))) )  
			commands.push(mActionBinding[pair.second]); 
	}  	
}

 bool Player::isRealtimeAction(Action act)
{
	if (act >= EndRealtimeactions)
		return false;
	else return true;
}

 sf::Keyboard::Key      Player::getAssignedKey(Action action) const
 {
	 for(auto pair : mKeyBinding) 
	 {
		 if(action == pair.second)
			 return pair.first;
	 }
	 return sf::Keyboard::Unknown;
 }

 void Player::assignKey()
 {
	mKeyBinding[sf::Keyboard::Unknown] = EndRealtimeactions;
	mActionBinding[EndRealtimeactions].action = derivedAction<Player>(PlayerMover(0.f,0.f));
	mActionBinding[EndRealtimeactions].category = Category::None;

	mKeyBinding[sf::Keyboard::Space] = Jump;
	mActionBinding[Jump].action = derivedAction<Player>(PlayerMover(0.f,-300.f));	
	mActionBinding[Jump].category = Category::RedPlayer;


 }