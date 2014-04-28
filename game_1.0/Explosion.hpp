#pragma once
class Explosion	:public SceneNode
{
public:
							Explosion(b2World*, b2Vec2, const TextureHolder&);
	virtual void	        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			updateCurrent(sf::Time);
							~Explosion(void);

	std::vector<sf::Sprite>				sprites;
	int									current;
	float								countdown;
	float								sinceLastUpd;
};

