#pragma once  
#include <memory>
#include <vector>
#include "SFML/Graphics.hpp"


struct Command;

class SceneNode : public sf::Transformable,
	public sf::Drawable,
	private sf::NonCopyable//конструктор копирования недоступен
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode(void);

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

