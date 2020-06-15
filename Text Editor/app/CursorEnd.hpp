#ifndef CURSOREND_HPP
#define CURSOREND_HPP

#include "Command.hpp"


class CursorEnd: public Command
{
public:
	void execute(EditorModel& model) override;

	void undo(EditorModel& model) override;

private:
	int curr_x;
	int curr_y;
};



#endif