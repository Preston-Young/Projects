#include "Backspace.hpp"
#include "EditorException.hpp"


void Backspace::execute(EditorModel& model)
{
	curr_x = model.cursorColumn();
	curr_y = model.cursorLine();
	curr_data = model.line(curr_y);

	if (curr_x == 1 && curr_y == 1) // If cursor is at the first spot of text
	{
		throw EditorException{"Already at beginning"};
	}

	else if (curr_x == 1 && curr_y != 1) // If cursor is at beginning of a line
	{
		prev_data = model.line(curr_y - 1);
		std::string new_data = prev_data + curr_data;
		model.setLine(new_data, curr_y - 1);
		model.delLine(curr_y);
		model.setCursorColumn(prev_data.length() + 1);
		model.setCursorLine(curr_y - 1);
	}

	else
	{
		std::string new_data = curr_data.substr(0, curr_x - 2) + curr_data.substr(curr_x - 1, curr_data.length());
		model.setLine(new_data, curr_y);
		model.setCursorColumn(curr_x - 1);
	}
	
}


void Backspace::undo(EditorModel& model)
{
	if (model.cursorLine() != curr_y)
	{
		model.setLine(prev_data, curr_y - 1); // Reset the previous line
		model.insertLine(curr_data, curr_y); // Add the deleted line with the old data

	}
	
	else
	{
		model.setLine(curr_data, curr_y);
	}
	
	model.setCursorColumn(curr_x);
	model.setCursorLine(curr_y);
}