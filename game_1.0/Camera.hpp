#pragma once
//#include "SFML/System.hpp"
//#include "Ground.hpp"
//#include "SceneNode.hpp"


class Camera
{
public:
	sf::View			view;
	sf::Vector2f		viewCenter;

						Camera(sf::View);
	void				setTarget(SceneNode*);
	void				update();

private:
	SceneNode*			target;
	//World*				world;
};

