#pragma once

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)>    derivedAction(Function fn)
{  
	return [=] (SceneNode& node, sf::Time dt) 
	{       
		assert(dynamic_cast<GameObject*>(&node) != nullptr);
			fn(static_cast<GameObject&>(node), dt); 
	}; 
} 