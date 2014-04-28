#pragma once
class Wreck : public SceneNode
{
	enum _lifetime 
	{
		immortal = 0,
		sec1,
		sec2,
		sec3,
		sec4,
		sec5 = 5,
		sec7 = 7,
		sec15 = 15
	};

public:
	sf::CircleShape			mShape;
	b2Body*					body;
	_lifetime				lifetime;
	sf::Time				t;

							Wreck(b2World*, const b2Vec2, const TextureHolder&);
	virtual void	        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			updateCurrent(sf::Time);
	virtual unsigned int    getCategory() const;
							~Wreck(void);
};

