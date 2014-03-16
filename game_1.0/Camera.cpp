#include "Camera.hpp"


Camera::Camera(sf::View _view)
	:view(_view),
	viewCenter(sf::Vector2f(0.f,0.f))
{
}

void Camera::update()
{
	view.move(target->getPosition() - viewCenter);
	viewCenter = target->getPosition();
}

void Camera::setTarget(SceneNode* newTarget)
{
	target = newTarget;
}