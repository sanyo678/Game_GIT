#include "Ground.hpp"


Ground::Ground(const TextureHolder& textures)
	:mSprite(textures.get(Textures::Ground))
{
	mSprite.setPosition(0.0f,0.0f);
}

void Ground::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

Ground::~Ground(void)
{
}
