#pragma once
#include "SFML/System.hpp"
#include "Ground.hpp"
#include "SceneNode.hpp"


class Camera
{
public:
	sf::View			view;

						Camera(sf::View);
	void				setTarget(SceneNode*);
	void				update();

private:
	sf::Vector2f		viewCenter;
	SceneNode*			target;
	//World*				world;
};

