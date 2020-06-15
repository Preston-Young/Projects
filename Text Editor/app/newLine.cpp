#include "newLine.hpp"


void newLine::execute(EditorModel& model)
{
	curr_x = model.cursorColumn();
	curr_y = model.cursorLine();
	curr_data = model.line(curr_y);

	int end = model.line(curr_y).length() + 1;

	if (curr_x == 1)
	{
		model.insertLine("", curr_y);
	}
	else if (curr_x == end)
	{
		model.insertLine("", curr_y + 1);
	}
	else
	{
		std::string prev_string = curr_data.substr(0, curr_x - 1);
		std::string next_string = curr_data.substr(curr_x - 1, curr_data.length());
		model.setLine(prev_string, curr_y);
		model.insertLine(next_string, curr_y + 1);
	}

	model.setCursorColumn(1);
	model.setCursorLine(curr_y + 1);
}


void newLine::undo(EditorModel& model)
{
	model.delLine(curr_y);
	model.setLine(curr_data, curr_y);
	model.setCursorColumn(curr_x);
	model.setCursorLine(curr_y);
}