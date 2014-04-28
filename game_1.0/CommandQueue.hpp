#pragma once
//#include "Command.hpp"
//#include <queue> //для std::queue<>
class CommandQueue
{
public:
	void        push(const Command& command);  
	Command     pop();
	bool        isEmpty() const;
	std::queue<Command> mQueue; 
}; 