#pragma once
//#include "SFML/Graphics.hpp"
//#include "Textures.hpp"
//#include "SceneNode.hpp"
//#include <list>

class Ground : public SceneNode
{
public:
	sf::Sprite				mSprite;
	std::list<b2Vec2>		edges;
	b2Body*					groundBody;

							Ground(const TextureHolder&, b2World*);
							~Ground(void);
	virtual void	        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			updateCurrent(sf::Time dt);
	void					build(b2World*);
	void					makeHole(b2Vec2, float);
							

private:
	b2BodyDef				groundBodyDef;
};

