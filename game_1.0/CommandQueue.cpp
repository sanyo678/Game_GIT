#include "headers.hpp"

void CommandQueue::push(const Command& command)
{
	mQueue.push(command);
}

Command CommandQueue::pop()
{
	Command tempCommand = mQueue.front();
	mQueue.pop();
	return tempCommand;
}

bool CommandQueue::isEmpty() const
{
	return mQueue.empty();
}
