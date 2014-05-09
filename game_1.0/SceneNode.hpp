#pragma once  

struct Command;

class SceneNode : public sf::Transformable,
	public sf::Drawable,
	private sf::NonCopyable//конструктор копирования недоступен
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
								SceneNode(b2World*);
	b2World*					pWorld;
	b2Vec2						position;
	float						rotation;
	bool						isDead;
	b2Vec2						playerPos;
	b2Vec2						explosionImpulse;

	void						attachChild(Ptr Child);
	Ptr							detachChild(const SceneNode& node);
	void						update(sf::Time dt);
	virtual unsigned int		getCategory() const;
	void					    onCommand(const Command& command, sf::Time dt);
	void						removeDead();
	bool						isToKill() const;

private:
	virtual void				draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void				drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void				updateCurrent(sf::Time dt);
	void						updateChildren(sf::Time dt);
	sf::Transform				getWorldTransform() const;

protected:
	std::vector<Ptr>			mChildren;
	SceneNode*					mParent;	
};

