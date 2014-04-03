#pragma once  
//#include <memory>
//#include <vector>
////#include "SFML/Graphics.hpp"
////#include "Box2D/Box2d.h"
//#include <algorithm> //find_if
//#include "assert.h"



struct Command;

class SceneNode : public sf::Transformable,
	public sf::Drawable,
	private sf::NonCopyable//конструктор копирования недоступен
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
					SceneNode(b2World*);
	b2World*		pWorld;
	b2Vec2			position;

	void			attachChild(Ptr Child);
	Ptr				detachChild(const SceneNode& node);
	void			update(sf::Time dt);
	virtual unsigned int    getCategory() const;
	void            onCommand(const Command& command, sf::Time dt);

private:
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void	updateCurrent(sf::Time dt);
	void			updateChildren(sf::Time dt);
	sf::Transform	getWorldTransform() const;

private:
	std::vector<Ptr>	mChildren;
	SceneNode*			mParent;	
};

