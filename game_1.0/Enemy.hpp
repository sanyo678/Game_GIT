#pragma once

class Enemy: public SceneNode
{
public:
							Enemy(b2World*, b2Vec2, const TextureHolder&);
	virtual void	        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			updateCurrent(sf::Time);
	virtual unsigned int    getCategory() const;
							~Enemy(void);

	b2Body*					body;
	sf::Sprite				mSprite1l;
	sf::Sprite				mSprite1r;
	sf::Sprite				mSprite2l;
	sf::Sprite				mSprite2r;
	float					countdown;
	float					spriteCountDown;
	int						hp;
	bool					firstSprite;
};

