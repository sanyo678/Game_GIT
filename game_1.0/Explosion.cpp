#include "headers.hpp"


Explosion::Explosion(b2World* _pw, b2Vec2 pos, const TextureHolder& textures)
	:SceneNode(_pw),
	countdown(0.64),
	sinceLastUpd(0)
{
	position = pos;
	sprites.push_back(sf::Sprite(textures.get(Textures::Explosion),sf::IntRect(0,0,64,64)));
	sprites.push_back(sf::Sprite(textures.get(Textures::Explosion),sf::IntRect(64,0,64,64)));
	sprites.push_back(sf::Sprite(textures.get(Textures::Explosion),sf::IntRect(128,0,64,64)));
	sprites.push_back(sf::Sprite(textures.get(Textures::Explosion),sf::IntRect(192,0,64,64)));
	sprites.push_back(sf::Sprite(textures.get(Textures::Explosion),sf::IntRect(0,64,64,64)));
	sprites.push_back(sf::Sprite(textures.get(Textures::Explosion),sf::IntRect(64,64,64,64)));
	sprites.push_back(sf::Sprite(textures.get(Textures::Explosion),sf::IntRect(128,64,64,64)));
	sprites.push_back(sf::Sprite(textures.get(Textures::Explosion),sf::IntRect(192,64,64,64)));
	sprites.push_back(sf::Sprite(textures.get(Textures::Explosion),sf::IntRect(0,128,64,64)));
	sprites.push_back(sf::Sprite(textures.get(Textures::Explosion),sf::IntRect(64,128,64,64)));
	sprites.push_back(sf::Sprite(textures.get(Textures::Explosion),sf::IntRect(128,128,64,64)));
	sprites.push_back(sf::Sprite(textures.get(Textures::Explosion),sf::IntRect(192,128,64,64)));
	sprites.push_back(sf::Sprite(textures.get(Textures::Explosion),sf::IntRect(0,192,64,64)));
	sprites.push_back(sf::Sprite(textures.get(Textures::Explosion),sf::IntRect(64,192,64,64)));
	sprites.push_back(sf::Sprite(textures.get(Textures::Explosion),sf::IntRect(128,192,64,64)));
	sprites.push_back(sf::Sprite(textures.get(Textures::Explosion),sf::IntRect(192,192,64,64)));

	current = 0;
	sf::FloatRect bounds = sprites[current].getLocalBounds();
	sprites[current].setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	sprites[current].setScale(6,6);
}

void Explosion::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprites[current],states);
}

void Explosion::updateCurrent(sf::Time dt)
{
	countdown -= dt.asSeconds();
	sinceLastUpd += dt.asSeconds();
	if (sinceLastUpd >= 0.04)
	{
		current++;
		sf::FloatRect bounds = sprites[current].getLocalBounds();
		sprites[current].setOrigin(bounds.width / 2.f, bounds.height / 2.f);
		sprites[current].setScale(6,6);
		sinceLastUpd = 0.0;
	}
	if (countdown <= 0.0)
		isDead = true;
}



Explosion::~Explosion(void)
{
}
