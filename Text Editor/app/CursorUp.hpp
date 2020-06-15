#ifndef CURSORUP_HPP
#define CURSORUP_HPP

#include "Command.hpp"



class CursorUp: public Command
{
public:
	void execute(EditorModel& model) override;

	void undo(EditorModel& model) override;

private:
	int curr_x;
	int curr_y;
};



#endif