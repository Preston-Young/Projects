#ifndef INSERTCHAR_HPP
#define INSERTCHAR_HPP

#include "Command.hpp"
#include <string>



class InsertChar: public Command
{
public:
	// Overloaded the constructor so I can have access to the key that the user pressed.
	InsertChar(char key);

	void execute(EditorModel& model) override;
	void undo(EditorModel& model) override;

private:
	int curr_x;
	int curr_y;
	std::string _key;
	std::string curr_data;
};



#endif