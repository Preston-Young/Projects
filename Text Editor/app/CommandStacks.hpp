#ifndef COMMANDSTACKS_HPP
#define COMMANDSTACKS_HPP

#include "Command.hpp"
#include <vector>



class Stacks
{
public:
	// Constuctor takes no arguments and initializes an empty stack
	Stacks();

	// Since stack is full of dynamica pointers to Commands, I need a
	// deconstructor that handles all the deallocation
	~Stacks();

	// Pushes to the top of the stack
	void push(Command* command);

	// Pops from the top of the stack and then returns it. I made it 
	// return the command from the top because now it'll double as a
	// helper function for the transfer member function
	Command* pop();

	// Returns the command at the top of the stack
	Command* top();

	// Returns the size of the stack
	int size();

	// Returns whether or not the stack is empty
	bool isEmpty();

	// Clears the entire stack--mainly for clearing the redo stack after
	// a new command is executed and there's nothing to redo. But it also
	// doubles as a helper function for the deconstructor
	void clear();

private:
	// I chose to implement my stack using a vector, since it comes with
	// many built in methods. I chose not to use std::stacks because I
	// don't know how to iterate through it and a vector gets the job done
	// just fine
	std::vector<Command*> stack;


};



#endif