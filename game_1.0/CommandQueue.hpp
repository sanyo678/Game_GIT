#pragma once

class CommandQueue
{
public:
	void        push(const Command& command);  
	Command     pop();
	bool        isEmpty() const;
	std::queue<Command> mQueue; 
}; 