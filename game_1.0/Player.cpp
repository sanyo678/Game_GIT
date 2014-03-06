#pragma once
#include "Player.hpp"
#include <iostream>


Player::Player(const TextureHolder& textures)
	: mSprite(textures.get(Textures::Player)), 
	  mType(Red)
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
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

 