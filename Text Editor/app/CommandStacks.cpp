// Vector-Based Stack Class to storer the commands

#include "CommandStacks.hpp"
#include "Command.hpp"
#include <vector>


Stacks::Stacks()
{
}


Stacks::~Stacks()
{
	Stacks::clear();
}


void Stacks::push(Command* command)
{
	stack.push_back(command);
}


Command* Stacks::pop()
{
	Command* tempCommand = stack.back();
	stack.pop_back();

	return tempCommand;
}


Command* Stacks::top()
{
	return stack.back();
}


int Stacks::size()
{
	return stack.size();
}


bool Stacks::isEmpty()
{
	if (stack.size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Stacks::clear()
{
	for (unsigned int i = 0; i < stack.size(); i++)
	{
		delete stack.at(i);
	}
	stack.clear();
}