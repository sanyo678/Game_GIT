#pragma once
//#include "SFML/Graphics.hpp"
//#include "Textures.hpp"
//#include "SceneNode.hpp"
//#include <list>

class Ground : public SceneNode
{
	struct hole
	{
		sf::CircleShape sh;
		float radius;
		b2Vec2 center;
		hole(float _rad, b2Vec2 _cent);
	};

	struct point
	{
		int num;
		std::list<b2Vec2>::iterator itr;
		point(int, std::list<b2Vec2>::iterator);
		point();
	};

public:
	sf::Sprite				background;
	std::list<b2Vec2>		edges;
	b2Body*					groundBody;
	sf::RenderTexture		rTexture;
	sf::Sprite				mSprite;
	sf::Sprite				mSky;
	std::vector<hole>		mHoles;
	std::vector<hole>		newHoles;
	bool                    toReBuild;
	const TextureHolder&	mTextures;
	SceneNode*				wreckHolder;
	std::list<b2Fixture*>   fixtures;

							Ground(const TextureHolder&, b2World*, SceneNode*);
							~Ground(void);
	virtual void	        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			updateCurrent(sf::Time dt);
	void					build(b2World*);
	void					makeHole(b2Vec2, float, point&, point&);
	virtual unsigned int    getCategory() const;
	void					explosion(b2Vec2, float);
	void					makeWrecks();
							

private:
	b2BodyDef				groundBodyDef;
};

